#include <stdio.h>

int add(int a, int b)
{
    return a+b;
}

int main(int argc, char *argv[])
{
    int x;
    x = add(10, 20);
    printf("%d\n", x);
    return 0;
}
