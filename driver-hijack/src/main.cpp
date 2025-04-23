#include <iostream>
#include "drv/driver.h"

int main()
{
    if (!drv::connect())
    {
        printf("[!] Error Connecting To Driver.\n");
        std::cin.get();
        return 1;
    }
    printf("[+] Connect To Driver.\n");

    DWORD ver = drv::get_drv_version();
    if (ver != 0x1020005)
    {
        printf("[!] Driver Version Does Not Match.\n");
        std::cin.get();
        return 1;
    }
    printf("[+] Driver Version Correct.\n");

    void* target = (void*)0xC0000; // test read bios section
    void* buffer = 0;
    size_t return_size = 0;
    if (drv::read_physical_memory(target, &buffer, sizeof(void*), &return_size))
    {
        printf("buffer -> %llx | return_size -> %d\n", buffer, return_size);
    }

    std::cin.get();
    drv::disconnect();
    return 0;
}
