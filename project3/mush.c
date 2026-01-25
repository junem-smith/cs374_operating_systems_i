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
    
    if (strcmp(tokens[0], "cd") == 0){
        int c = chdir(tokens[1]);
        if (c==-1){
            perror("No such directory");
            exit(1);
        }
    } else if (strcmp(tokens[0], "exit") == 0){
        exit(0);
    }
    else{
        run_command(tokens);
    }

}

int run_command(char *tokens[]) {
    char *cmd = tokens[0];
    pid_t pid = fork();

    if(pid == 0){
        // fork is a child
        execvp(cmd, tokens);
        perror("Command execution failed.");
        exit(1);
    } else {
        // fork is a parent
        wait(NULL);
    }
    
}



