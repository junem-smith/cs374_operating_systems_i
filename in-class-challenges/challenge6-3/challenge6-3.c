#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

//  Alt: make sig_handler

void sigusr1_handler(int sig)
{
    (void)sig;
    write(1, "SIGUSR1 handled\n", 16);
}

int main(void) {
    struct sigaction sa = {
        .sa_handler = sigusr1_handler,
        .sa_flags = SA_RESTART, // or SA_RESTART
    };
    
    char buf[128];

    puts("Reading from the keyboard. But don't type anything.");
    printf("Go to another window and `kill -USR1 %d`\n", getpid());

    int st = read(0, buf, sizeof buf);

    if (st == -1) {
        perror("read");
    }

}


