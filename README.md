# Hijack Vulnerable Driver

In this project, I am hijacking a vulnerable driver known as WinRing0x64.sys and manipulating its DeviceIoControl in order to give me access to read physical memory from usermode. I did this through static reverse engineering of the binary in IDA. The main function shows an example usage of reading the UEFI section of the physical memory.
