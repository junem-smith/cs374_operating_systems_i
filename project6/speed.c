#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

volatile sig_atomic_t speed;

void sigusr1_handler(int sig)
{
    (void)sig;
    if (speed > 0){
        speed--;
    }
}
void sigusr2_handler(int sig)
{
    (void)sig;
    speed++;
}

int main(void) {
    //  commands user can enter: -, +, q
    // Do not allow the speed to go below 0 under any circumstances. IT WOULD BE BAD. 
    // WORMHOLE.
    struct sigaction sa1 = {
        .sa_handler = sigusr1_handler,
        .sa_flags = 0,
    };
    sigemptyset(&sa1.sa_mask);
    sigaction(SIGUSR1, &sa1, NULL);
    
    struct sigaction sa2 = {
        .sa_handler = sigusr2_handler,
        .sa_flags = 0,
    };
    sigemptyset(&sa2.sa_mask);
    sigaction(SIGUSR2, &sa2, NULL);
    

    sigset_t block_mask, empty_mask;
    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGUSR1);
    sigaddset(&block_mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &block_mask, NULL);



    // process PID
    pid_t pid = getpid();
    printf("PID=%d\n", pid);
    
    while(1){
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        int psel = pselect( 1, &readfds, NULL, NULL, NULL, &empty_mask );
        if (psel == -1) continue;

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            char arg[1028];
            
            read(STDIN_FILENO, &arg, 1);

            char* ptr = arg;

            int new = speed;
            while (*ptr != '\0'){
                

                if (*ptr == 'q'){
                    // quit
                    exit(1);
                }
                if (*ptr == '+') {
                    new ++;
                    kill(getpid(), SIGUSR2);
                    printf("increase speed to: %d\n", new);
                }
                else if (*ptr == '-') {
                    if(speed > 0) new--;
                    kill(getpid(), SIGUSR1);
                    printf("decrease speed to: %d\n", new);
                }
                ptr++;
            }
        }
    
    }
    

    


}


