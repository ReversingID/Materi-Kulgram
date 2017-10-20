/*
As a victim for various exercise of DLL injection.

Compile:
    GCC
    $ gcc runme.c -L. -lvictim -o runme

    MSVC
    $ cl /nologo runme.c victim.lib
Run:
    $ runme

*/

#include <stdio.h>
#include <string.h>
#include <process.h>
#include <windows.h>

int f(int n);

int __declspec(dllimport) add(int a, int b);
int __declspec(dllimport) sub(int a, int b);
int __declspec(dllimport) mul(int a, int b);

typedef int (__stdcall* func_ptr)(int, int);
func_ptr pointers[3];

int global = 135;

int main()
{
    int i = 0;
    int choice = 0;
    int x, y;

    HMODULE  handle;

    handle = GetModuleHandleA("victim.dll");
    pointers[0] = (func_ptr) GetProcAddress(handle, "add");
    pointers[1] = (func_ptr) GetProcAddress(handle, "sub");
    pointers[2] = (func_ptr) GetProcAddress(handle, "mul");

    printf("My PID is %d\n\n", _getpid());

    do
    {
        printf("Menu ----\n");
        printf("1. Call f() 10 times\n");
        printf("2. List modules\n");
        printf("3. Call add,sub,mul (imported from victim.dll)\n");
        printf("4. Show value of global\n");
        printf("0. Exit\n");
        printf("Your choice? (1/2/3/4): ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 0:
                printf("Exiting...");
                break;
            case 1:
                printf("f() is at ( 0x%p )\n", f);
                for (i=0; i<10; i++)
                {
                    printf("%d ", i);
                    f(i);
                    Sleep(1000);
                }
                break;
            case 2:
                printf("add ( 0x%p ) == pointers[0] ( 0x%p )\n", add, pointers[0]);
                printf("sub ( 0x%p ) == pointers[1] ( 0x%p )\n", sub, pointers[1]);
                printf("mul ( 0x%p ) == pointers[2] ( 0x%p )\n", mul, pointers[2]);
                break;
            case 3:
                x = 15;
                y = 5;
                printf("operation on X=15 and Y=5\n");
                printf("add(X,Y) = %d\n", add(x,y));
                printf("sub(X,Y) = %d\n", sub(x,y));
                printf("mul(X,Y) = %d\n", mul(x,y));
                break;
            case 4:
                printf("(0x%p) global = %d\n", &global, global);
                break;
            default:
                printf("No such choice!\n");
                break;
        }

        printf("\n\n");
    } while (choice != 0);
}

int f(int n)
{
    printf("Got number: %d\n", n);
}