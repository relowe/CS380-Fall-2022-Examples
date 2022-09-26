/*
 Unix Memory Model

            Bottom - +------------+
        (low address)| Text (ro)  |  Code
                     +------------+
                     | Data (rw)  |  Global Variables 
                     |            |  Heap (malloc, free)
                     |            |
                     +------------+------ Program Break
                         ...
                       Unallocated
                          Space
                         ...
                     +------------+
                     |  Stack     |
           Top       +------------+
        (High Address)
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    void *pbrk;     /* Program Break */
    int inc;        /* Increment */
    unsigned char *ptr; 

    ptr = malloc(1);
    printf("Heap Segment Begins: %p\n", ptr);

    pbrk = sbrk(0);
    for(;;) {
        ptr = pbrk;

        // allow the user to increment sbrk
        printf("Current Break: %p\n", pbrk);
        printf("Increment? ");
        scanf("%d", & inc);
        pbrk = sbrk(inc);

        // fill the data segment
        printf("I am filling my data segment with 0x2A\n");
        for(void *p = ptr ; p < pbrk; p++) {
            *(unsigned char *)p = 0x2a;
        }
    }
}
