#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 

int main(void)
{
    int fd;

    char buf[128];
    fd = open("foo.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }


    int bytes_read = read(fd, buf, 128);

    while (bytes_read > 0){
        write(1, buf, bytes_read);
        bytes_read = read(fd, buf, 128);
        
    }
    
    close(fd);
}