#include <cpu.h>

cpu_info core_count() {


#ifdef _WIN32

    // Windows

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);

    return sysinfo.dwNumberOfProcessors;

#else

    // Unix

    size_t eax = 11, ebx = 0, ecx = 1, edx = 0;

    __asm__ volatile("cpuid"
          : "=a" (eax),
            "=b" (ebx),
            "=c" (ecx),
            "=d" (edx)
          : "0" (eax), "2" (ecx)
          : );

    cpu_info info;

    info.eax = eax;
    info.ebx = ebx;
    info.edx = edx;
    info.cores = sysconf(_SC_NPROCESSORS_ONLN);

#endif

    return info;
}
