/*
Inject this DLL to a process.
Find add, sub, and mul on process' IAT and then patch them.

using gcc:
	gcc -shared -o iatpatch.dll iatpatch.c
using MSVC:
	cl /nologo /LD /0x /GS /sdl iatpatch.c
*/
#include <windows.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct 
{
    LPBYTE addr_original;
    LPBYTE addr_hooking;
} IAT_ENTRY;

HMODULE  module;
SIZE_T   imp_size;
PIMAGE_IMPORT_DESCRIPTOR imp_desc;

int patch_init()
{
    module = GetModuleHandleA(NULL);

    // Get DOS header
    PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)module;

    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
    {
        printf("e_magic is not valid DOS signature\n");
        return 0;
    }

    // Get the NT header from the DOS header
    PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((LPBYTE)dos_header + dos_header->e_lfanew);

    // Get the import descriptor from the NT header
    imp_desc = (PIMAGE_IMPORT_DESCRIPTOR)((LPBYTE)dos_header + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    // The size also from NT headers
    imp_size = (SIZE_T) ((LPBYTE)dos_header + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size);

    return 1;
}

IAT_ENTRY *  patch_it(const char* target_func, LPVOID newfunction)
{
    IAT_ENTRY * retval = NULL;

    // We have enough information to start making the loops to the function pointer.
    // Every PE has its own IMAGE_IMPORT_DESCRIPTOR
    // Find the correct function and then patch it
    
    for (IMAGE_IMPORT_DESCRIPTOR * iid = imp_desc; iid->Name != NULL; iid++) 
    {
        for (int func_idx = 0; *(func_idx + (LPVOID*)(iid->FirstThunk + (SIZE_T)module)) != NULL; func_idx++) 
        {
            char * name = (char*)(*(func_idx + (SIZE_T*)(iid->OriginalFirstThunk + (SIZE_T)module)) + (SIZE_T)module + 2);
            
            if (!_stricmp(target_func, name))
            {
                retval = (IAT_ENTRY*)malloc(sizeof(IAT_ENTRY));
                void** func_ptr = (func_idx + (LPVOID*)(iid->FirstThunk + (SIZE_T)module));
                
                DWORD oldrights, newrights = PAGE_READWRITE;
                VirtualProtect(func_ptr, sizeof(LPVOID), newrights, &oldrights);
                retval->addr_original = *func_ptr;
                *func_ptr = newfunction;
                retval->addr_hooking = newfunction;
                VirtualProtect(func_ptr, sizeof(LPVOID), oldrights, &newrights);

                break;
            }
        }
    }

    return retval;    
}

void patch_restore(IAT_ENTRY * iat_entry)
{
    free(patch_it(iat_entry->addr_hooking, iat_entry->addr_original));
}

int __declspec(dllexport) add(int a, int b)
{
    printf("\nNot real ADD!\n");
	return a + b + 2;
}

int __declspec(dllexport) sub(int a, int b)
{
    printf("\nNot real SUB!\n");
    return a - b + 2;
}

int __declspec(dllexport) mul(int a, int b)
{
    printf("\nNot real MUL!\n");
	return a * b + 2;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID lpres)
{
    IAT_ENTRY * iat_add;
    IAT_ENTRY * iat_sub;
    IAT_ENTRY * iat_mul;
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            patch_init();
            iat_add = patch_it("add", (LPVOID)add);  // add
            iat_sub = patch_it("sub", (LPVOID)sub);  // sub
            iat_mul = patch_it("mul", (LPVOID)mul);  // mul
            break;
        case DLL_PROCESS_DETACH:
            patch_restore(iat_add);
            patch_restore(iat_sub);
            patch_restore(iat_mul);
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