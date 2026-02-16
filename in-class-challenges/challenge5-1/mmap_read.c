#include <stdio.h>
#include <unistd.h>
#define DATA_SIZE 1024

int main(int argc, char *argv[]){
    int i = atoi(argv[1]);
    float f = atof(argv[2]);
    char *s = argv[3]

    fd = open("data.dat", O_RDWR, 0644);
    void *data = mmap(NULL, DATA_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    
    // Compute the pointer positions into the data
    
    // Store the int, float, and string (with strcpy()) into the memory-mapped region.
    char *c = (char *)data;
    strcpy(c, ("READ: %i, %f, %s", i, f, s));
    printf(c);
    // munmap() the file
    munmap(data, sizeof data);
    close(fd);

}
