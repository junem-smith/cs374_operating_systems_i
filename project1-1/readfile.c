#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 

int main(int argc, char *argv[]) {

    int fd;
    char buf[2048];

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    int bytes_read = read(fd, buf, 2048);
    write(1, buf, bytes_read);

    close(fd);
    
}