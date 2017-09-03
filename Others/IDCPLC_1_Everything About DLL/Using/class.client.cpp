/*
Simple client to use dll. 
The dll has .lib which is used to create definition of IAT

using gcc:
	$ g++ class.client.cpp -o class.client.exe -L. -lcfoo
using MSVC:
	$ cl /nologo class.client.cpp cfoo.lib
	
run:
	simple.client.exe
*/
#include <windows.h>

#ifdef _MSC_VER
#pragma comment(lib,"kernel32")
#pragma comment(lib,"user32")
#pragma comment(linker,"/subsystem:windows /entry:main")
#endif

#include "CFoo.hpp"

#ifdef __cplusplus
extern "C" {
#endif

int main()
{
	CFoo cf;
	MessageBox(NULL, TEXT("Testing"), TEXT("Title"), MB_OK | MB_ICONINFORMATION);
	
	return 0;
}


#ifdef __cplusplus
}
#endif