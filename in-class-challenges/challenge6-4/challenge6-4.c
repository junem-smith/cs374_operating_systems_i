#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t usr1_happened;

void sigusr1_handler(int sig)
{
    (void)sig;
    usr1_happened = 1;
    // printf("Go to another window and `kill -USR1 %d`\n", getpid());
}

int main(void)
{
    struct sigaction sa = {
        .sa_handler = sigusr1_handler,
        .sa_flags = 0,
    };

    sigemptyset(&sa.sa_mask);

    
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("Go to another window and `kill -USR1 %d`\n", getpid());
    
    while (!usr1_happened)
        sleep(10);
    puts(("Go to another window and `kill -USR1 %d`\n", getpid()));

}