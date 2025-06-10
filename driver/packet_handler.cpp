#include "imports.h"
#include "server_shared.h"
#include "sockets.h"

static uint64_t handle_copy_memory(const PacketCopyMemory& packet)
{
	PEPROCESS dest_process = nullptr;
	PEPROCESS src_process = nullptr;

	if (!NT_SUCCESS(PsLookupProcessByProcessId(HANDLE(packet.dest_process_id), &dest_process)))
	{
		return uint64_t(STATUS_INVALID_CID);
	}

	if (!NT_SUCCESS(PsLookupProcessByProcessId(HANDLE(packet.src_process_id), &src_process)))
	{
		ObDereferenceObject(dest_process);
		return uint64_t(STATUS_INVALID_CID);
	}

	SIZE_T   return_size = 0;
	NTSTATUS status = MmCopyVirtualMemory(
		src_process,
		(void*)packet.src_address,
		dest_process,
		(void*)packet.dest_address,
		packet.size,
		UserMode,
		&return_size
	);

	ObDereferenceObject(dest_process);
	ObDereferenceObject(src_process);

	return uint64_t(status);
}

static uint64_t handle_get_base_address(const PacketGetBaseAddress& packet)
{
	PEPROCESS process = nullptr;
	NTSTATUS  status = PsLookupProcessByProcessId(HANDLE(packet.process_id), &process);

	if (!NT_SUCCESS(status))
		return 0;

	const auto base_address = uint64_t(PsGetProcessSectionBaseAddress(process));
	ObDereferenceObject(process);

	return base_address;
}

static uint64_t handle_free_process_memory(const PacketGetBaseAddress& packet)
{
	PEPROCESS process = nullptr;
	NTSTATUS  status = PsLookupProcessByProcessId(HANDLE(packet.process_id), &process);

	if (!NT_SUCCESS(status))
		return 0;

	const auto base_address = uint64_t(PsGetProcessSectionBaseAddress(process));
	ObDereferenceObject(process);

	return base_address;
}

bool complete_request(const SOCKET client_connection, const uint64_t result)
{
	Packet packet{ };

	packet.header.magic = packet_magic;
	packet.header.type = PacketType::packet_completed;
	packet.data.completed.result = result;

	return send(client_connection, &packet, sizeof(packet), 0) != SOCKET_ERROR;
}

static uintptr_t get_kernel_address(const char* name, size_t& size) {
	NTSTATUS status = STATUS_SUCCESS;
	ULONG neededSize = 0;

	ZwQuerySystemInformation(
		SystemModuleInformation,
		&neededSize,
		0,
		&neededSize
	);

	PSYSTEM_MODULE_INFORMATION pModuleList;

	pModuleList = (PSYSTEM_MODULE_INFORMATION)ExAllocatePool(NonPagedPool, neededSize);

	if (!pModuleList) {
		return 0;
	}

	status = ZwQuerySystemInformation(SystemModuleInformation,
		pModuleList,
		neededSize,
		0
	);

	ULONG i = 0;
	uintptr_t address = 0;

	for (i = 0; i < pModuleList->ulModuleCount; i++)
	{
		SYSTEM_MODULE mod = pModuleList->Modules[i];

		address = uintptr_t(pModuleList->Modules[i].Base);
		size = uintptr_t(pModuleList->Modules[i].Size);
		if (strstr(mod.ImageName, name) != NULL)
			break;
	}

	ExFreePool(pModuleList);

	return address;
}

static uint64_t clean_piddb_cache() {
	PRTL_AVL_TABLE PiDDBCacheTable;

	size_t size;
	uintptr_t ntoskrnlBase = get_kernel_address("ntoskrnl.exe", size);

	PiDDBCacheTable = (PRTL_AVL_TABLE)dereference(find_pattern<uintptr_t>((void*)ntoskrnlBase, size, "\x48\x8d\x0d\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x3d\x00\x00\x00\x00\x0f\x83", "xxx????x????x????xx"), 3);

	if (!PiDDBCacheTable) {
		return 0;
	}

	uintptr_t entry_address = uintptr_t(PiDDBCacheTable->BalancedRoot.RightChild) + sizeof(RTL_BALANCED_LINKS);

	piddbcache* entry = (piddbcache*)(entry_address);

	/*capcom.sys(drvmap) : 0x57CD1415 iqvw64e.sys(kdmapper) : 0x5284EAC3, also cpuz driver*/
	if (entry->TimeDateStamp == 0x57CD1415 || entry->TimeDateStamp == 0x5284EAC3) {
		entry->TimeDateStamp = 0x54EAC3;
		entry->DriverName = RTL_CONSTANT_STRING(L"monitor.sys");
	}

	ULONG count = 0;
	for (auto link = entry->List.Flink; link != entry->List.Blink; link = link->Flink, count++)
	{
		piddbcache* cache_entry = (piddbcache*)(link);

		if (cache_entry->TimeDateStamp == 0x57CD1415 || cache_entry->TimeDateStamp == 0x5284EAC3) {
			cache_entry->TimeDateStamp = 0x54EAC4 + count;
			cache_entry->DriverName = RTL_CONSTANT_STRING(L"monitor.sys");
		}
	}

	return 1;
}

static uint64_t clean_unloaded_drivers() {
	ULONG bytes = 0;
	auto status = ZwQuerySystemInformation(SystemModuleInformation, 0, bytes, &bytes);

	if (!bytes)
		return 0;

	PRTL_PROCESS_MODULES modules = (PRTL_PROCESS_MODULES)ExAllocatePool(NonPagedPool, bytes);

	status = ZwQuerySystemInformation(SystemModuleInformation, modules, bytes, &bytes);

	if (!NT_SUCCESS(status)) {
		ExFreePool(modules);
		return 0;
	}

	PRTL_PROCESS_MODULE_INFORMATION module = modules->Modules;
	uintptr_t ntoskrnlBase = 0;
	size_t ntoskrnlSize = 0;

	ntoskrnlBase = get_kernel_address("ntoskrnl.exe", ntoskrnlSize);

	ExFreePool(modules);

	if (ntoskrnlBase <= 0) {
		return 0;
	}

	// NOTE: 4C 8B ? ? ? ? ? 4C 8B C9 4D 85 ? 74 + 3 + current signature address = MmUnloadedDrivers
	auto mmUnloadedDriversPtr = find_pattern<uintptr_t>((void*)ntoskrnlBase, ntoskrnlSize, "\x4C\x8B\x00\x00\x00\x00\x00\x4C\x8B\xC9\x4D\x85\x00\x74", "xx?????xxxxx?x");

	if (!mmUnloadedDriversPtr) {
		return 0;
	}

	uintptr_t mmUnloadedDrivers = dereference(mmUnloadedDriversPtr, 3);

	memset(*(uintptr_t**)mmUnloadedDrivers, 0, 0x7D0);

	return 1;
}

// below functions is what i wrote -breww

static uint64_t FreeVirtualMemory(const PacketFreeProcessMemory& packet)
{
	PEPROCESS process = NULL;

	NTSTATUS status = PsLookupProcessByProcessId((HANDLE)packet.pid, &process);
	if (process == NULL)
	{
		return 0; // process doesn't exist
	}
	PVOID base_address = (PVOID)packet.base;
	KAPC_STATE apc;

	KeStackAttachProcess(process, &apc);
	SIZE_T region_size = 0;
	status = ZwFreeVirtualMemory(ZwCurrentProcess(), &base_address, &region_size, MEM_RELEASE);
	DbgPrint("FreeVirtualMemory Status:%x", status);
	KeUnstackDetachProcess(&apc);
	ObDereferenceObject(process);
	return 1;
}

#if 0 // was using this for learning kernel functions, do not compile.
static uint64_t ReadProcessMemory(const PacketReadProcessMemory& packet)// HANDLE pid, PVOID64 address, PVOID64 buffer, DWORD size)
{
	PEPROCESS source_process = nullptr;
	PEPROCESS target_process = nullptr;

	if (!NT_SUCCESS(PsLookupProcessByProcessId(HANDLE(packet.self), &source_process))) //check if usermode id is valid cuz we mmcopy to usernmode
	{
		return uint64_t(STATUS_INVALID_CID);
	}

	if (!NT_SUCCESS(PsLookupProcessByProcessId(HANDLE(packet.pid), &target_process))) //check if target is valid
	{
		ObDereferenceObject(source_process);
		return uint64_t(STATUS_INVALID_CID);
	}

	PEPROCESS process = NULL;
	NTSTATUS status = PsLookupProcessByProcessId((HANDLE)packet.pid, &process);
	if (process == NULL)
	{
		return 0; // process doesn't exist
	}
	SIZE_T real_size;

	status = MmCopyVirtualMemory(process, (void*)packet.address, source_process, (void*)packet.buffer, packet.size, UserMode, &real_size);

	ObDereferenceObject(process);
	return status;

}
#endif

static uint64_t ProtectVirtualMemory(const PacketProtectVirtualMemory& packet)
{
	PRKPROCESS process = NULL;
	NTSTATUS status = PsLookupProcessByProcessId((HANDLE)packet.pid, &process);
	if (process == NULL)
	{
		return 0; // process doesn't exist
	}
	KAPC_STATE apc;
	PVOID base_address = (void*)packet.base;
	SIZE_T protect_size = packet.size;
	ULONG old_protect;
	KeStackAttachProcess(process, &apc);
	status = ZwProtectVirtualMemory(ZwCurrentProcess(), &base_address, &protect_size, packet.protection, &old_protect);
	KeUnstackDetachProcess(&apc);
	ObDereferenceObject(process);

	return 1;
}

static uint64_t AllocateVirtualMemory(const PacketAllocateVirtualMemory& packet)
{

	PEPROCESS process = NULL;
	NTSTATUS status = PsLookupProcessByProcessId((HANDLE)packet.pid, &process);
	if (process == NULL)
	{
		return 0; // failed no process
	}
	PVOID base_address = NULL;
	KAPC_STATE apc;

	size_t real_size = packet.size;
	KeStackAttachProcess(process, &apc);
	status = ZwAllocateVirtualMemory(ZwCurrentProcess(), &base_address, 0, &real_size, MEM_COMMIT, packet.protect);

	KeUnstackDetachProcess(&apc);
	ObDereferenceObject(process);
	return reinterpret_cast<uint64_t>(base_address); // returns base address of allocated memory

}







uint64_t handle_incoming_packet(const Packet& packet)
{
	switch (packet.header.type)
	{
	case PacketType::packet_copy_memory:
		return handle_copy_memory(packet.data.copy_memory);

	case PacketType::packet_get_base_address:
		return handle_get_base_address(packet.data.get_base_address);

	case PacketType::packet_clean_piddbcachetable:
		return clean_piddb_cache();

	case PacketType::packet_clean_mmunloadeddrivers:
		return clean_unloaded_drivers();

	// my functions below -breww
	case PacketType::packet_free_process_memory:
		return FreeVirtualMemory(packet.data.free_memory);

	case PacketType::packet_allocate_process_memory:
		return AllocateVirtualMemory(packet.data.allocate_memory);

	case PacketType::packet_protect_process_memory:
		return ProtectVirtualMemory(packet.data.protect_memory);

	default:
		break;
	}

	return uint64_t(STATUS_NOT_IMPLEMENTED);
}
