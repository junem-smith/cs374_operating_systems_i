#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/stat.h>


int main(int argc, char *argv[])
{
    (void)argc;
    struct stat buf;
    
    if (argc == 1){
        printf("usage: getsize file [ file ... ]\n");
    } else {
        for (int i = 1; i < argc; i++){
            stat(argv[i], &buf); // '&' address of operator, turns buf into a pointer
            printf("%s: %ld\n", argv[i], buf.st_size);
        }
    }
    

    
}