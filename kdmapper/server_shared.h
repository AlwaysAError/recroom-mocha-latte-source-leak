#pragma once
#include "stdint.h"

constexpr auto packet_magic = 0x12345568;
constexpr auto server_ip = 0x7F000001; // 127.0.0.1
constexpr auto server_port = 29144;

/*                    breww's Migrated Functions Table Guide
	##---------------------------------------------------------------------------------##
	||	  Packet Header	    ||	     Function        ||       PacketType Class         ||
	||---------------------------------------------------------------------------------||
	||					    ||			             ||                                ||
	||  protect_memory      -> ProtectVirtualMemory  -> packet_protect_process_memory  ||
	||  allocate_memory     -> AllocateVirtualMemory -> packet_allocate_process_memory ||
	||  free_memory         -> FreeVirtualMemory     -> packet_free_process_memory     ||
	##---------------------------------------------------------------------------------##
	*
	* this exists in usermode but it uses the
	* copy_memory function
	*
	* write_process_memory -> write_memory
*/

enum class PacketType
{
	packet_copy_memory,
	packet_get_base_address,
	packet_clean_piddbcachetable,
	packet_clean_mmunloadeddrivers,
	packet_completed,

	// my packets below -breww
	packet_free_process_memory,
	packet_allocate_process_memory,
	packet_protect_process_memory
};

struct PacketFreeProcessMemory
{
	uint32_t pid;
	uint64_t base;
};


struct PacketReadProcessMemory
{
	uint32_t pid;
	uint64_t address;
	uint32_t self;
	uint64_t buffer;
	size_t size;
};

struct PacketProtectVirtualMemory
{
	uint32_t pid;
	uint64_t base;
	size_t size;
	ULONG protection;
};

struct PacketAllocateVirtualMemory
{
	uint32_t pid;
	size_t size;
	ULONG protect;
};

struct PacketCopyMemory
{
	uint32_t dest_process_id;
	uint64_t dest_address;
	uint32_t src_process_id;
	uint64_t src_address;
	uint32_t size;
};

struct PacketGetBaseAddress
{
	uint32_t process_id;
};

struct PacketGetProcessId
{
	char* process_name;
};

struct PacketCleanPiDDBCacheTable {
};

struct PacketCleanMMUnloadedDrivers {
};

struct PacketSpoofDrives {
};

struct PackedCompleted
{
	uint64_t result;
};

struct PacketHeader
{
	uint32_t   magic;
	PacketType type;
};

struct Packet
{
	PacketHeader header;
	union
	{
		PacketFreeProcessMemory free_memory;
		PacketProtectVirtualMemory protect_memory;
		PacketAllocateVirtualMemory allocate_memory;

		// ^ above is my cool ones :sunglasses: -breww

		PacketCopyMemory	 copy_memory;
		PacketGetBaseAddress get_base_address;
		PacketCleanPiDDBCacheTable clean_piddbcachetable;
		PacketCleanMMUnloadedDrivers clean_mmunloadeddrivers;
		PacketSpoofDrives	 spoof_drives;
		PackedCompleted		 completed;
	} data;
};
