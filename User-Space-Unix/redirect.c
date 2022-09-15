#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    /* redirect my program's output to a file */
    close(1); /* close std out */
    open("stdout.txt", O_CREAT|O_WRONLY|O_TRUNC, 0600);

    printf("Hello, world\n");
}
