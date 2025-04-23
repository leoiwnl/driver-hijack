#include "driver.h"

bool drv::connect()
{
	handle = CreateFile(L"\\\\.\\WinRing0_1_2_0", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (handle == INVALID_HANDLE_VALUE)
		return false;

	return true;
}

DWORD drv::get_drv_version()
{
	DWORD version, bytesReturned;
	BOOL success = DeviceIoControl(handle, version_code, NULL, 0, &version, sizeof(version), &bytesReturned, NULL); // lpInBuffer == MasterIrp ig
	if (!success)
	{
		printf("[!] Error Getting Driver Version. Code: %d\n", GetLastError());
		return 0;
	}

	return version;
}

bool drv::read_physical_memory(void* target, void* buffer, size_t size, size_t* return_size)
{
	ReadMemoryStruct r; PHYSICAL_ADDRESS addr;
	addr.QuadPart = (LONGLONG)target;
	r.physical_address = addr;
	r.element_size = 1;
	r.count = size;

	DWORD bytes_returned = 0;
	BOOL success = DeviceIoControl(handle, read_code, &r, sizeof(r), buffer, size, &bytes_returned, NULL);
	if (!success)
	{
		printf("[!] Error Reading. Code: %d\n", GetLastError());
		return false;
	}

	*return_size = bytes_returned;
	return *return_size == size;
}

void drv::disconnect()
{
	CloseHandle(handle);
}
