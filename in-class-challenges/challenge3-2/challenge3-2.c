
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("And...\n");

    pid_t pid = fork();

    if(pid == 0){
        // fork is a child
        execlp("ls", "ls", NULL);
    } else {
        // fork is a parent
        printf("I'm the parent\n");
        wait(NULL);
        
    }
    printf("We're done\n");


}