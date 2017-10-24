/*
Inject this DLL to a process.
Show messagebox with greeting text

using gcc:
	gcc -shared -o entrypoint.dll entrypoint.c
using MSVC:
	cl /nologo /LD /0x /GS /sdl entrypoint.c
*/
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
Reference: https://msdn.microsoft.com/en-us/library/windows/desktop/ms682583(v=vs.85).aspx

DLL_PROCESS_ATTACH:
    DLL is being loaded into the virtual address space of the current process.
DLL_PROCESS_DETACH:
    DLL is being unloaded from the virtual address space because of:
        1. loaded unsuccessfully
        2. reference count has reached zero.
            2.1 processes is terminated
            2.2 FreeLibrary is called (for each LoadLibrary call)
DLL_THREAD_ATTACH:
    Current process is creating a new thread and calls the entry-point function of all DLLs currently attached.
DLL_THREAD_DETACH:
    Thread is existing cleanly.
*/


BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID lpres)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            MessageBoxA(NULL, TEXT("DLL Injected. DllMain is called from process attach."), TEXT("Greeting"), MB_OK);
            break;
        case DLL_PROCESS_DETACH:
            MessageBoxA(NULL, TEXT("DllMain is called from process detach."), TEXT("Greeting"), MB_OK);
            break;
        case DLL_THREAD_ATTACH:
            MessageBoxA(NULL, TEXT("DllMain is called from thread attach."), TEXT("Greeting"), MB_OK);
            break;
        case DLL_THREAD_DETACH:
            MessageBoxA(NULL, TEXT("DllMain is called from thread detach."), TEXT("Greeting"), MB_OK);
            break;
    }
	return 1;
}

#ifdef __cplusplus
}
#endif