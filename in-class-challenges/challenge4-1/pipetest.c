#include <stdio.h>
#include <string.h>


int main() {
    int pfds[2]; 
    const char *buf[128];

    pipe(pfds);

    printf("%d, %d\n", pfds[0], pfds[1]);

    
    write(pfds[1], "Hello\n", 6);
    int bytes_read = read(pfds[0], buf, sizeof buf);
    
    write(1, buf, bytes_read);

}