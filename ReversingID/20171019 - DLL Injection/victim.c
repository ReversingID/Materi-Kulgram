/*
Export three functions to be imported by runme

Compilation
	using gcc
	$ gcc -shared -o victim.dll -Wl,--out-implib,libvictim.a victim.c

	using MSVC
	$ cl /nologo /LD /Ox /GS /sdl victim.c
*/

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

int __declspec(dllexport) add(int a, int b)
{
	return a + b;
}

int __declspec(dllexport) sub(int a, int b)
{
    return a - b;
}

int __declspec(dllexport) mul(int a, int b)
{
	return a * b;
}

BOOL WINAPI _DllMainCRTStartup(HINSTANCE hinst, DWORD dwReason, LPVOID lpres)
{
	return 1;
}

#ifdef __cplusplus
}
#endif