#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//  fork() returns 0 to child process, child PID to the parent

int main() {
    int pfds[2]; 
    const char *buf[128];
    pid_t pid;

    pipe(pfds);

    pid = fork();

    if (pid == 0) {
        close(pfds[0]);
        write(pfds[1], "Hello, parent!\n", 15);
        exit(0);
    } else {
        close(pfds[1]);
        int bytes_read = read(pfds[0], buf, sizeof buf);
        write(1, buf, bytes_read);
        wait(NULL);
    }

}

