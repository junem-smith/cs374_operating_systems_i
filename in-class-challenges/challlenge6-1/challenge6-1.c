#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

//  Alt: make sig_handler

int main(void) {

    struct sigaction sa = {
        .sa_handler = DFL,
        .sa_flags = 0
    }

    if (sigaction(SIGINT, &sa, NULL) == -1){
        perror("sigaction");
        exit(1);
    }
    sigemptyset(&sa.sa_mask);
    puts("^C locked out for 5 seconds! Try it!\n");
    sleep(5);
    
    
    struct sigaction sa = {
        .sa_handler = SIG_IGN,
        .sa_flags = 0
    }
    sigemptyset(&sa.sa_mask);
    puts("^C reenabled! Try it!");
    sleep(10);
    
}


