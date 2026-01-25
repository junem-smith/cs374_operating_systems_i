#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int run_command(char *tokens[]);

int main()
{
    
    char line[2048];
    char *tokens[128] = {0};

    printf("prompt> "); fflush(stdout);
    fgets(line, sizeof line, stdin);

    char *token;
    int i = 0;

    if ((token = strtok(line, " \n")) != NULL) do {
        tokens[i] = token;
        i++;
    }
    while ((token = strtok(NULL, " \n")) != NULL);
    
    run_command(tokens);
    

}

int run_command(char *tokens[]) {
    char *cmd = tokens[0];
    pid_t pid = fork();

    if(pid == 0){
        // fork is a child
        execvp(cmd, tokens);
    } else {
        // fork is a parent
        wait(NULL);
    }
    
}


