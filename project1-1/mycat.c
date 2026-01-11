#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 

int main(int argc, char *argv[]) {

    int fd; 
    int bytes_read;
    char buf[2048];

    if (argc == 1){
        fd = 0;
        bytes_read = read(fd, buf, 2048);
        while (bytes_read > 0){
            write(1, buf, bytes_read);
            bytes_read = read(fd, buf, 2048);
        }
    }
    else {
        for (int i = 1; i < argc; i++){
            fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                    perror("open");
                    return 1;
                }
            bytes_read = read(fd, buf, 2048);
            while (bytes_read > 0){
                write(1, buf, bytes_read);
                
                bytes_read = read(fd, buf, 2048);
            }
            
            close(fd);
        }
    }
    
}
