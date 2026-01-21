
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("And...\n");

    pid_t pid = fork();

    if(pid == 0){
        // fork is a child
        printf("I'm the child\n");
    } else {
        // fork is a parent
        printf("I'm the parent\n");
        
    }
    printf("We're done\n");


}