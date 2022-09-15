#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int p[2]; // my pipe
    char buf[100];
    int i;

    pipe(p);

    // write to the write side of the pipe
    write(p[1], "hello", 5);

    // read from the read side of the pipe
    i = read(p[0], buf, 100);

    // print the buffer
    buf[i] = '\0';
    printf("%s\n", buf);
}
