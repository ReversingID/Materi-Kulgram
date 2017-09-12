#include <stdio.h>

int main(void)
{
    int x;
    printf("Enter the secret number : ");
    scanf("%d", &x);
    if(x*3 == 1443)
        printf("Good (Y)\n");
    else
        printf("Bad :(\n");
}
