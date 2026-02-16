#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

//  Alt: make sig_handler

void sig_handler((void) sig (int))
{
    const char msg[200];
    struct sigaction sa = {
        .sa_handler = sig,
        .sa_flags = 0
    }
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1){
        perror("sigaction");
        exit(1);
    }
    printf("Enter a string:\n");
    
    if (fgets(msg, sizeof msg, stdin) == NULL){
        perror("fgets");
        exit(1);
    }
    
    write(1, "Got SIGINT!\n", 12);

}

int main(void) {

    
    puts("^C locked out for 5 seconds! Try it!\n");
    sleep(5);
    sig_handler(SIG_RESTART);
    puts("Program will exit in 10 seconds. Hit ^C!");
    sleep(10);
    
}


