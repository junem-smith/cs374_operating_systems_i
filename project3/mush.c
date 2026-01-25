#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int run_command(char *tokens[]);

int main()
{
    while(1){
        char line[2048];
        char *tokens[128] = {0};

        printf("prompt> "); fflush(stdout);
        fgets(line, sizeof line, stdin);
        
        if (strcmp(line, "\n") == 0){
            continue;
        }
        else if (feof(stdin)){
            exit(0); 
        }

        char *token;
        int i = 0;

        if ((token = strtok(line, " \n")) != NULL) do {
            tokens[i] = token;
            i++;
        }
        while ((token = strtok(NULL, " \n")) != NULL);

        int argc = sizeof(tokens);
        if (argc == 0){ // if there are no arguments, then go to start of loop.
            continue;
        }
        
        // Check if first argument is change directory
        if (strcmp(tokens[0], "cd") == 0){
            if (argc != 2){
                fprintf(stderr, "usage: cd directory\n");}
            
            int c = chdir(tokens[1]);
            
            if (c==-1){
                perror("No such directory");
                exit(1);
            }
        }
        else {
            run_command(tokens);
        }
}
}

int run_command(char *tokens[]) {
    char *cmd = tokens[0];
    if (strcmp(cmd, "exit") == 0){
        exit(0);
    }
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



