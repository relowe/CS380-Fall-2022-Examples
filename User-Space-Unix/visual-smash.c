#include <stdio.h>
#include <string.h>

/********************************************************************* 
 * Structures and Type Defintions  (and macros)
 ********************************************************************/
struct variable_info {
    char name[40];
    void *ptr; 
    int size;
};


/********************************************************************* 
 Function Prototypes
 ********************************************************************/
struct variable_info build_info(char name[], void *ptr, int size);
void stack_experiment();
void visualize_stack(void *sp, void *bp, struct variable_info *vars, int n);


/********************************************************************* 
 * Main Function 
 ********************************************************************/
int main()
{
    stack_experiment();
}


/********************************************************************* 
 * Function Definitions 
 ********************************************************************/

/* Construct a variable_info structure */
struct variable_info build_info(char name[], void *ptr, int size)
{
    struct variable_info info;

    /* populate the info fields */
    strncpy(info.name, name, 40);
    info.name[39] = '\0';
    info.ptr = ptr;
    info.size = size;

    return info;
}


/* Visualize and endanger the stack */
void stack_experiment()
{
    char buf[60];
    int i;
    void *ptr;
    void *end;
    struct variable_info vars[5] = {
        build_info("buf", &buf, sizeof(buf)),
        build_info("i", &i, sizeof(i)),
        build_info("ptr", &ptr, sizeof(ptr)),
        build_info("end", &end, sizeof(end)),
        build_info("vars", &vars, sizeof(vars)) 
    };

    /* find the beginning (top) of the stack */
    asm("mov %%rsp, %0" : "=rm"(ptr));

    /* find the bottom of the stack */
    asm("mov %%rbp, %0" : "=rm" (end));

    printf("Enter some text: ");
    gets(buf);

    visualize_stack(ptr, end, vars, 5);

}


void visualize_stack(void *sp, void *bp, struct variable_info *vars, int n)
{
    struct variable_info *vptr;
    void *ptr;

    /* print each stack address and visualize stuff */
    for(ptr = sp; ptr <= bp+sizeof(void*) * 2; ptr++) {
        printf("%p 0x%02x", ptr, (unsigned int) *((char*)ptr));
        for(vptr = vars; vptr < vars+n; vptr++) {
            if(ptr == vptr->ptr) {
                printf("\t\t%s", vptr->name);
            }
        }
        if(ptr == bp) {
            printf("\t\tBase Pointer");
        } else if(ptr == bp + sizeof(void*)) {
            printf("\t\tReturn Address");
        }
        putchar('\n');
    }
}
