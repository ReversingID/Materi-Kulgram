/*
DLL with exporting C++ class

Compilation
	using gcc
	$ g++ -shared -o cfoo.dll -Wl,--out-implib,libcfoo.a cfoo.cpp

	using MSVC
	$ cl /nologo /LD /Ox /GS /sdl cfoo.cpp
*/

#define __EXPORT_CLASS_

#include <windows.h>
#include <string.h>
#include "CFoo.hpp"

#ifdef _MSC_VER
#pragma comment(lib,"user32")
#pragma warning(disable:4996)
#endif

BOOL WINAPI _DllMainCRTStartup()
{
	return 1;
}

CFoo::CFoo()
{
	memset(m_internal, 0, sizeof(m_internal));
}

int CFoo::add(int i, int j)
{
	strcpy(m_internal, "CFoo::add()");
	return (i+j);
}

int CFoo::sub(int i, int j)
{
	strcpy(m_internal, "CFoo::sub()");
	return (i-j);
}

char * CFoo::last_function()
{
	return m_internal;
}