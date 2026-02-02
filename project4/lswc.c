#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int pfds[2];
    pid_t pid;
    char *dir;
    dir = argv[1];
    if (argc == 1){
        dir = ".";
    }
    else if (argc > 2){
        perror("Usage: lswc <directory>\n");
        return 1;
    }
    // Parse the command line
    
    // Make a pipe in the parent
    pipe(pfds);
    pid = fork();
    
    if (pid == 0) { // The child will run wc:
        // dup2 the read end of the pipe into stdin
        int stdin = dup2(pfds[0], 0);
        // close the write end of the pipe
        close(pfds[1]);
        // execlp the wc command
        execlp("wc", "wc", "-l", (char *)NULL);
        exit(1);
    }
    else {  // The parent will run ls:
        // dup2 the write end of the pipe into stdout
        int stdout = dup2(pfds[1], 1);
        // close the read end of the pipe
        close(pfds[0]);
        // execlp the ls command
        execlp( "ls", "-1a", dir, (char *)NULL);
    }
    
}
