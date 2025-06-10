#include "driver.h"

extern void NTAPI server_thread(void*);

VOID MyThread()
{
    PsTerminateSystemThread(STATUS_SUCCESS);
}

NTSTATUS RealEntry(PDRIVER_OBJECT  DriverObject, PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);

	HANDLE thread_handle = nullptr;

	// Create server thread that will wait for incoming connections.
	const auto status = PsCreateSystemThread(
		&thread_handle,
		GENERIC_ALL,
		nullptr,
		nullptr,
		nullptr,
		server_thread,
		nullptr
	);

	if (!NT_SUCCESS(status))
	{
		return STATUS_UNSUCCESSFUL;
	}

	ZwClose(thread_handle);
	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT  DriverObject, PUNICODE_STRING RegistryPath
)
{
    return STATUS_SUCCESS;
}