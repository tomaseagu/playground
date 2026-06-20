#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *address = (int *) malloc(sizeof(int));
    
    printf("bytes of sizeof(int): %zu bytes\n", sizeof(int));

    if (address == NULL)
    {
        printf("Error: not enough space.\n");
	return 1;
    }

    *address = 42;

    unsigned long long address_saved = (unsigned long long) address;
    printf("address of saved int: 0x%llx\n\n", address_saved);

    int data = *address;
    printf("Saved data: %d", data);

    free(address);

    return 0;
}
	
