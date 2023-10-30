#ifndef __CPU_H
#define __CPU_H

#include <stdlib.h>
#include <stdio.h>

typedef struct core_data {
    size_t cores;
    size_t eax;
    size_t ebx;
    size_t edx;
} cpu_info ;

#ifdef __unix__

    #define OS_Windows 0
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

#elif defined(_WIN32) || defined(WIN32)

    #define OS_Windows 1
    #include <windows.h>
    #include <stdio.h>
    #include <tchar.h>
		#include <sysinfoapi.h>

#endif

cpu_info core_count();

#endif
