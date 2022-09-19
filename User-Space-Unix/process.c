/*
 Process is the basic unit of separation.
  - When the kernel starts, it creates and init process.
  - init process creates the user space system.


 Main Process System Calls
   - int fork() - Creates an exact duplicate of the current process.
      Returns:   0 - Child
               pid - Parent
   - exec(file, argv) - replaces the current process with the 
      program located in file.
   - int wait(int *) - waits for one of your children to die
       - returns pid of the exited child
       - optional int* is used to retrieve the child's exit status
   - int getpid() - returns the current process's id
   - exit(int) - Terminates a process
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid;
    char * exec_argv[2] = { 0x00, 0x00 };
    char buf[100];

    // create a copy of myself
    pid = fork();

    if(pid) { // 0 is false, all others are true
        // parent
        printf("I spawned process %d\n", pid);
    } else {
        // child
        printf("I am the child. My process id is %d\n", getpid());
        printf("What would you like me to run? ");
        fgets(buf, 100, stdin);
        
        //build argv
        buf[strlen(buf)-1] = '\0'; //kill newline
        exec_argv[0] = buf;
        execvp(exec_argv[0], exec_argv);
        printf("Exec is done.\n");
        exit(0);
    }

    pid = wait(NULL);
    printf("My child process has terminated itself.\n");
    printf("It's pid was: %d\n", pid);
}
