#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_RECORDS 1048576
#define BYTES 32

[int offset]
[int count]


struct flock hlock = {
    .l_type=F_WRLCK, // Or F_RDLCK for a read lock
    .l_whence=SEEK_SET,
    .l_start = 0,
    .l_len = sizeof(int) * 2,
};
struct flock rlock = {
    .l_type = F_WRLCK,	/* setting a write lock */
 	.l_whence = SEEK_SET,	/* offset l_start from beginning of file */
 	.l_start = 0,
 	.l_len = BYTES,
};
struct flock lock = {
    .l_type=F_WRLCK, // Or F_RDLCK for a read lock
    .l_whence=SEEK_SET,
    .l_start=0,
    .l_len=0,
};
int acquire_lock(int fd){
    lock.l_type = F_WRLCK;
    return fcntl(fd, F_SETLKW, &lock);
}
int release_lock(int fd){
    lock.l_type = F_UNLCK;
    return fcntl(fd, F_SETLKW, &lock);
    
}
int acquire_hlock(int fd){
    hlock.l_type = F_WRLCK;
    return fcntl(fd, F_SETLKW, &hlock);
    
}
int release_hlock(int fd){
    hlock.l_type = F_UNLCK;
    return fcntl(fd, F_SETLKW, &hlock);
    
}

int acquire_rlock(int fd, int offset){
    rlock.l_type = F_WRLCK;
    rlock.l_start = sizeof(int) * 2 + offset;
    return fcntl(fd, F_SETLKW, &rlock);
}
int release_rlock(int fd){
    rlock.l_type = F_UNLCK;
    return fcntl(fd, F_SETLKW, &rlock);
}


int main(int argc, char *argv[]) {
    
    if ((argc + 1) % 2 != 0 || argc < 3) {
        perror("Usage: lswc <line count> <file> ...\n");
        return 1;
    }

    size_t filesize = sizeof(int) * 2 + MAX_RECORDS * BYTES;

    // open the log file
    int fd = open("log.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    ftruncate(fd, filesize);
    
    void *base = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    int children = 0;

    //  Main Run
    for (int i = 1; i < argc; i+=2 ){
        char *prefix = argv[i+1];
        int n = atoi(argv[1 + 2*i]);
        // launch a child process with fork()
        pid_t pid = fork();
        
        if(pid == 0) { 
            // Each child process will append the appropriate number and value of records.
            for (int k = 0; k < n; k++) {
                // Lock the header
                acquire_hlock(fd);
                int offset = ((int *)base)[0];
                int count = ((int *)base)[1];
                
                count++;            // Increment the count
                offset += BYTES;    // Set the offset in the header to its new value
                
                ((int *)base)[0] = count; 
                ((int *)base)[1] = offset; 

                release_hlock(fd);
                
                // Compute a pointer to where the new entry would be written
                char *ptr = (char*)base + sizeof(int)*2 + offset;

                acquire_rlock(fd);  // Lock the record where the write will occur.

                // Copy the new entry data to the address stored in the pointer.
                strcpy(ptr, prefix);
                ptr[BYTES - 1] = '\0';
                
                release_rlock(fd);  // Unlock the record.
            }
            exit(0);
        }
        children++;
        
        
    


    }
    // The parent process calls wait(NULL) for every child process launched. 
        for (int i = 0; i < children; i++) {
        wait(NULL);
        }
        
        // dump the contents of the log to stdout.
        acquire_lock(fd);   // Lock the entire file.
        count = ((int *)base)[0]; // header count
        char *rb = (char *)base + sizeof(int) * 2;

        for (int j = 0; j < count; j++) {
            char *rec = rb + j * BYTES;
            printf("%d: %s\n", j, rec);
        }
        release_lock(fd);
    //  TODO: int munmap(void addr[.length], size_t length);
    munmap(base, filesize);
    close(fd);

}



