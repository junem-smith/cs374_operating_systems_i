#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define FIFO_NAME "test_fifo"


int main(int argc, char *argv[])
{
    
    char buf[128];
    int fd;
    
    mkfifo(FIFO_NAME, 0644);
    printf("Waiting for writers.\n");
    fd = open(FIFO_NAME, O_RDONLY); // Open file for reading
    printf("Found writer.\n");


    while(1){
        int bytes = read(fd, buf, sizeof buf);
        if (bytes == -1){
            perror("Error reading file");
        }
        if(bytes == 0){
            break;
        }

    }

    close(fd);
    exit(0);
}
