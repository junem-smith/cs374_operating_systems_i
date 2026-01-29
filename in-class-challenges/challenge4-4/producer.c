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
    if (argc!=2) {
        fprintf(stderr, "usage: producer data \n");
        return(1);
    }
    int fd;

    mkfifo(FIFO_NAME, 0644);
    fd = open(FIFO_NAME, O_WRONLY); // Open file for writing

    int num = strlen(argv[1]);

    write(fd, argv[1], num);

    close(fd);
    exit(0);
}
