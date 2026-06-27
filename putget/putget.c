#include <stdio.h>

int main()
{
    int c = getchar();

    while (c != EOF) {
        putchar(c);
        c = getchar();
        printf("\n%d\n", c != EOF);
    }

    return 1;

    /*
    int c;
    while ((c = getchar()) != EOF)
        printf("%c", c);
    
    return 1;
    */
}
