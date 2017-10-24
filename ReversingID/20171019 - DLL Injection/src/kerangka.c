/*
Skeleton of DLL file that will be injected to other process.

using gcc:
	gcc -shared -o kerangka.dll kerangka.c
using MSVC:
	cl /nologo /LD /0x /GS /sdl kerangka.c
*/
#include <windows.h>

/*
Windows API offers a number of functions that allow us to attach and manipulate into other
programs for debugging purposes.

The steps:
    - "Attach" to the process
    - "Allocate" memory within the process
    - "Copy" the DLL or the DLL path into process memory and determine appropriate memory address
    - "Execute" the DLL within process, instructing process to call the entry point in other thread 

*/

#ifdef __cplusplus
extern "C" {
#endif

/*
__declspec(dllexport) void function(int arguments)
{ 
	
}
*/

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID lpres)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
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