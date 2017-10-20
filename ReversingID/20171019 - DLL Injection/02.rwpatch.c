/*
Inject this DLL to a process.
Read and write certain memory region. In this case the global variable.

using gcc:
	gcc -shared -o rwpatch.dll rwpatch.c
using MSVC:
	cl /nologo /LD /0x /GS /sdl rwpatch.c
*/
#include <windows.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID lpres)
{
    int* global = NULL;

    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            global = (int*)0x404010;

            printf("\n\n");
            printf("Value of global = %d\n", *global);
            *global = 1337;
            printf("Value of global = %d\n", *global);
            break;
        case DLL_PROCESS_DETACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }
	return 1;
}

#ifdef __cplusplus
}
#endif