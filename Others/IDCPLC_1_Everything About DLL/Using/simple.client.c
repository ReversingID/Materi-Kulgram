/*
Simple client to use hello.dll. 
The dll has .lib which is used to create definition of IAT

using gcc:
	$ gcc simple.client.c -o simple.client.exe -L. -lhello
using MSVC:
	$ cl /nologo simple.client.c hello.lib
	
run:
	simple.client.exe
*/
#include <windows.h>

#ifdef _MSC_VER
#pragma comment(lib,"kernel32")
#pragma comment(lib,"user32")
#pragma comment(linker,"/subsystem:windows /entry:main")
#endif

#ifdef __cplusplus
extern "C" {
#endif

int main()
{
	// There would be a warning because we haven't declare world()
	world();
	
	return 0;
}


#ifdef __cplusplus
}
#endif