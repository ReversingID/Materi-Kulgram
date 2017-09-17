/*
Create DLL using definition file.

using gcc:
	$ gcc -shared -o hello2.dll -Wl,--out-implib,libhello.a hello2.c
	or
	$ gcc -shared -o hello2.dll hello2.c

using MSVC:
	$ cl /nologo /LD /Ox /GS /sdl hello2.c hello2.def
	
run:
	rundll32 hello.dll,world
*/

#include <windows.h>

#ifdef _MSC_VER
#pragma comment(lib,"advapi32")
#pragma comment(lib,"kernel32")
#pragma comment(lib,"user32")
#endif

#ifdef __cplusplus
extern "C" {
#endif

void world()
{
	DWORD dwtemp = 62;
	TCHAR szname[64], szbuff[MAX_PATH+1];
	
	if (GetUserName(szname, &dwtemp))
		wsprintf(szbuff, "Hello %s, how are you?", szname);
	else
		lstrcpyn(szbuff, "Hello stranger! :D", 18);
	MessageBox(NULL, szbuff, TEXT("Title"), MB_OK | MB_ICONINFORMATION);
}

BOOL WINAPI _DllMainCRTStartup(HINSTANCE hinst, DWORD dwReason, LPVOID lpres)
{
	return 1;
}

#ifdef __cplusplus
}
#endif