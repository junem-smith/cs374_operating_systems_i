#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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
    
    int status = system(tokens[0]);
    
    if (status != 0) {
        printf("%s is not a command.\n", tokens[0]) ;
        return main();
    }

    execvp(tokens[0], tokens);

}
