/*
using gcc:
	gcc -shared -o kerangka.dll kerangka.c -Wl,--out-implib,libkerangka.a
using MSVC:
	cl /nologo /LD /0x /GS /sdl kerangka.c
*/
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
__declspec(dllexport) void function(int arguments)
{ 
	
}
*/

/*
	DLL Entry point
	By default, this function is the entry point and will load C Run Time. It will then call the
	common DllMain() function which will be the initial user logic.
	Providing this function will make a minimum DLL without CRT 

	If you want to do something when Dll is attached, detached then use DllMain().
*/
BOOL WINAPI _DllMainCRTStartup(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved)
{
	return 1;
}

/*
BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH: 
		i = 135;
		break;
		case DLL_THREAD_ATTACH: break;
		case DLL_THREAD_DETACH: break;
		case DLL_PROCESS_DETACH: 
		MessageBox(NULL, TEXT("DETACHED from process"), TEXT("Title"), MB_OK | MB_ICONINFORMATION);
		break;
	}
}
*/

#ifdef __cplusplus
}
#endif