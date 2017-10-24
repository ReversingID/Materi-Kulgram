/*
Inject DLL to remote process

Compile:
    $ g++ injector -o injector

Run:
    $ injector <PID> <dll path>

*/

#include <windows.h>
#include <stdio.h>

/*
Idea:
    - Create new thread in remote / target process.
    - The new thread will execute our "DLL"

Process:
    - Get the process handle for PID
    - Allocate space for string of DLL path
    - Write DLL path to the process selected in step 1
    - Resolve address of kernel32.dll & LoadLibraryA function
    - Create new thread on remote target to execute LoadLibraryA with our DLL path as argument
*/

int inject(const int pid, const char* dll_path);

int main(int argc, char* argv[])
{
    int choice = 1;

    if (argc != 3) 
    {
        fprintf(stderr, "[!] Should have 3 arguments!\n");
        fprintf(stderr, "Usage: %s <PID> <dll path>", argv[0]);
        return 1;
    }

    return inject(atoi(argv[1]), argv[2]);
}

int inject(const int pid, const char* dll_path)
{
    HANDLE remote;
    HANDLE remote_thread;
    void * alloc_addr;
    int    dll_path_len = strlen(dll_path) + 1;
    int    write_result;

    int    error_code;
    char   error_message_buffer[256];

    printf("[+] Starting DLL Injector\n");

    // [1] Open the remote process
    // HANDLE OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
    printf("[+] Get process handle for PID: %d\n", pid);
    remote = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (remote == NULL)
    {
        error_code = GetLastError();
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), error_message_buffer, 256, NULL);
        fprintf(stderr, "[!] Cannot open the remote process!\nDetail: %d %s\n", error_code, error_message_buffer);
        return 1;
    }

    // [2] Allocating space in the process
    // LPVOID VirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
    printf("[+] Allocating space for DLL path\n");
    alloc_addr = VirtualAllocEx(remote, NULL, dll_path_len, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    if (alloc_addr == NULL)
    {
        CloseHandle(remote);

        error_code = GetLastError();
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), error_message_buffer, 256, NULL);
        fprintf(stderr, "[!] Cannot allocate memory on remote process!\nDetail: %d %s\n", error_code, error_message_buffer);
        return 2;
    }

    // [3] Write DLL path on remote process
    // BOOL WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T * lpNumberOfBytesWritten);
    printf("[+] Writing DLL path to current process space\n");
    SIZE_T num_written;
    write_result = WriteProcessMemory(remote, alloc_addr, dll_path, dll_path_len, &num_written);
    if (! write_result)
    {
        VirtualFreeEx(remote, alloc_addr, 0, MEM_RELEASE);
        CloseHandle(remote);

        error_code = GetLastError();
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), error_message_buffer, 256, NULL);
        fprintf(stderr, "[!] Cannot write to process memory!\nDetail: %d %s\n", error_code, error_message_buffer);
        return 3;
    }

    // [4] Resolve address of kernel32.dll & LoadLibraryA function
    // FARPROC GetProcAddress(HMODULE hModule,LPCSTR lpProcName);
    // HMODULE GetModuleHandleA(LPCSTR lpModuleName);
    printf("[+] Resolving call specific functions and libraries\n");
    HMODULE kernel_handle_addr = GetModuleHandleA("kernel32.dll");
    printf("\t[*] Resolved kernel32 library at 0x%08x\n", kernel_handle_addr);
    void * load_lib = (LPVOID) GetProcAddress(kernel_handle_addr, "LoadLibraryA");
    printf("\t[*] Resolved LoadLibraryA function at 0x%08x\n", load_lib);

    // [5] Create new thread on remote target to execute LoadLibraryA with our DLL path as argument
    // HANDLE CreateRemoteThread(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
    printf("[+] Creating Remote Thread to load our DLL\n");
    remote_thread = CreateRemoteThread(remote, NULL, 0, (LPTHREAD_START_ROUTINE) load_lib, alloc_addr, 0, NULL);
    if (remote_thread == NULL)
    {
        VirtualFreeEx(remote, alloc_addr, 0, MEM_RELEASE);
        CloseHandle(remote);

        error_code = GetLastError();
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), error_message_buffer, 256, NULL);
        fprintf(stderr, "[!] Cannote create remote thread!\nDetail: %d %s\n", error_code, error_message_buffer);
        return 4;
    }

    // DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
    WaitForSingleObject(remote_thread, INFINITE);
    VirtualFreeEx(remote, alloc_addr, 0, MEM_RELEASE);
    CloseHandle(remote);

    return 0;
}