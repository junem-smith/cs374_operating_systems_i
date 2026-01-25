#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    
    char line[1024];
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
    
    execvp(tokens[0], tokens);

}
