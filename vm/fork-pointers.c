#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int *ptr = malloc(sizeof(int));

    if(fork()) {
        /* parent */
        *ptr = 1;
    } else {
        /* child */
        *ptr = 2;
    }

    for(;;) {
        printf("%p: %d\n", ptr, *ptr);
    }
}
