#include <stdio.h>
#include <string.h>

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
    }  // do something with the token
    while ((token = strtok(NULL, " ")) != NULL);


    // Prints out the tokens
    for (int i = 0; tokens[i] != NULL; i++)
        printf("%d: %s\n", i, tokens[i]);

}
