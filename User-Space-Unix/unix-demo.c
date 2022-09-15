/*
 * UNIX
 *   - Simple Metaphor: Everything is a file.
 *     - Buffered Stream - Kernel maintains an associate between buffer and a number.
 *       write(int fd, void *buf, int count)
 *          fd - File Descriptor to which we write.
 *         buf - beginning of memory to write
 *       count - How many bytes do we want to write
 *      Returns: -1 on error, # of bytes written on success
 *
 *   File Descriptor
 *    An integer which specifies the file stream.
 *    Every UNIX application opens with the following:
 *      0 - stdin (keyboard)
 *      1 - stdout (screen)
 *      2 - stderr (screen)
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd;    // a file descriptor
    int fd2;

    /* A lower level hello world program */
    write(1, "Hello, World\n", 13);

    /* create a text file */
    fd = open("out.txt", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    fd2 = open("out2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    write(fd, "Hello, World\n", 13);
    write(fd2, "Goodbye, World\n", 15);
    close(fd);
    close(fd2);

    printf("fd: %d\nfd2: %d\n", fd, fd2);

    fd = open("out2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    write(fd, "Hello, World\n", 13);
    close(fd);
    printf("Third File: %d\n", fd);
}
