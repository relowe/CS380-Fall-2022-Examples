/* 
  IPC - Inter Process Communication
    - Pipes are how UNIX does IPC

  The basic pipeline idea.
    1.) Create a pipe.
    2.) Visualize your goal. 
                    Parent (shell)
                   |              |   
              +--------+      +--------+
              | Left  1|----->|0  Right|
              +--------+      +--------+
                     p[1]    p[0]
    3.) Fork the left side.
        1.) close(1)
        2.) dup(p[1])
        3.) close(p[1])
        4.) close(p[0])
        5.) exec....

    4.) Fork the right side.
        1.) close(0)
        3.) dup(p[0])
        4.) close(p[1])
        5.) close(p[0])
        6.) exec....

    5.) Close the parent's copy of the pipe
        close(p[0])
        close(p[1])

    6.) wait(...)
    7.) wait(...)
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int p[2]; // my pipe call
    char *const largv[] = { "cat", "-n", "pipeline.c", NULL };
    char *const rargv[] = { "less", NULL };

    // create the pipe
    if(pipe(p)) {
        // pipe failed
        fprintf(stderr, "Could not create pipe.\n");
        exit(-1);
    }

    // construct the pipeline: cat -n pipeline.c | less
    if(!fork()) {
        // left child process
        close(1);
        dup(p[1]);
        close(p[1]);
        close(p[0]);
        execvp(largv[0], largv);

        // error!
        fprintf(stderr, "Could not exec %s\n", largv[0]);
        exit(-2);
    }

    if(!fork()) {
        // right child process
        close(0);
        dup(p[0]);
        close(p[1]);
        close(p[0]);
        execvp(rargv[0], rargv);

        // error!
        fprintf(stderr, "Could not exec %s\n", rargv[0]);
        exit(-2);
    }

    // close the parent pipe
    close(p[0]);
    close(p[1]);

    // wait on our children
    wait(NULL);
    wait(NULL);
    printf("My children have been terminated.\n");


}
