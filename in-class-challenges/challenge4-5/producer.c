#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "test_fifo"

int main(int argc, char *argv[])
{
    if (argc!=2) {
        fprintf(stderr, "usage: producer data \n");
        return(1);
    }
    int fd;

    ////////////
    char buf[16];

    mkfifo(FIFO_NAME, 0644);
    fd = open(FIFO_NAME, O_WRONLY); // Open file for writing
    
    int num = strlen(argv[1]);

    int count = atoi(argv[1]);  // get integer from argument

    for (int i = 0; i < count; i++){
        buf[0] = i;
        strcpy(buf+1, ("Message #%d\n", i));  // set the message
        write(fd, buf, 16);
        sleep(1);   // I wish I were asleep
    }

    write(fd, FIFO_NAME, num);

    close(fd);
    exit(0);
}
