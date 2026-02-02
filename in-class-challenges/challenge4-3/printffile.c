#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("output.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644);
    if (fd == -1) {
        perror("open: Permission denied");
    }
    
    int stdout = dup2(fd, 1);

    // write(1, "hi!\n", 4);
    // write(stdout2, "HI!\n", 4);
    printf("%d\n", stdout);
    fflush(stdout);

    close(fd);
}

// How could you somehow "save" the old stdout so that
// you could cause printf() to start printing to the 
// screen again instead of to the file?

// Through a pipe