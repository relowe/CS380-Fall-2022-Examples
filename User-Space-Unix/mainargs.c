// demonstrate unix parameter passing
#include <stdio.h>

int main(int argc, char **argv, char **argenv) 
{
    int i;

    // the real format of the char **argv array is:
    // An array of pointers to strings
    //  [0] -> "/mainargs"
    //  [1] -> ""
    //  ...
    //  [argc] -> 0x00
    for(i=0; argv[i]; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    // the format for char **argenv is also null terminate
    for(i=0; argenv[i]; i++) {
        printf("argenv[%d] = %s\n", i, argenv[i]);
    }

}
