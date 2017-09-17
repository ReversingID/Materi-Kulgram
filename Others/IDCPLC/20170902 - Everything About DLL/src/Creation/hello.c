/*
Simple DLL creation with import lib

Compilation
	using gcc
	$ gcc -shared -o hello.dll -Wl,--out-implib,libhello.a hello.c

	using MSVC
	$ cl /nologo /LD /Ox /GS /sdl hello.c
	
run
	rundll32 hello.dll,world
*/

#include <windows.h>

#ifdef _MSC_VER
#pragma comment(lib,"user32")
#endif

#ifdef __cplusplus
extern "C" {
#endif

void __declspec(dllexport) world()
{
	MessageBox(NULL, TEXT("This is a message"), TEXT("Title"), MB_OK | MB_ICONINFORMATION);
}

BOOL WINAPI _DllMainCRTStartup(HINSTANCE hinst, DWORD dwReason, LPVOID lpres)
{
	return 1;
}

#ifdef __cplusplus
}
#endif