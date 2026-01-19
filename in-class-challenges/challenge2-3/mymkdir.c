#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    if (argc != 2){
        perror("usage");
        return 1;
    }
    
    mkdir(argv[1], 0777);
    return 0;
}
