#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

// redirects output into a file
int main(int argc, char *argv[]){
    if (argc <= 2) {
        perror("usage: redirout filename command [arg1 [arg2 ... ] ]\n");
        return 1;
    }
    // open() the output file
    int fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
    if (fd == -1){
        perror("Failed to open file");
        return 1;
    }
    dup2(fd, 1);

    char *cmd[128];
    int index = 0;
    for (int i = 2; i < argc; i++){
        cmd[index] = argv[i];
        index++;
    }
    cmd[index] = NULL;
    execvp( argv[2], cmd );
    close(fd);
}
