#pragma once
#include <windows.h>
#include <iostream>

constexpr DWORD version_code = 0x9C402000;
constexpr DWORD status_code = 0x9C402004;
constexpr DWORD read_code = 0x9C406104;

typedef LARGE_INTEGER PHYSICAL_ADDRESS, * PPHYSICAL_ADDRESS;
struct ReadMemoryStruct
{
	PHYSICAL_ADDRESS physical_address;
	uint32_t element_size; // 1, 2 or 4
	uint32_t count;
};

namespace drv
{
	inline HANDLE handle;

	bool connect();
	DWORD get_drv_version();
	bool read_physical_memory(void* target, void* buffer, size_t size, size_t* return_size);
	void disconnect();
}