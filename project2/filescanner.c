#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 500
int getsize(char *path);

int main(int argc, char *argv[])
{
    const char *dir = argv[1];
    if (argc > 2){
        fprintf(stderr, "usage: filescanner [directory]\n");
        return 1;
    }
    if (argc == 1){
        dir = ".";
        
    }
    
    getsize(dir);

}


// Recursive function to go through each directory and get the size
int getsize(char *path)
{
    DIR *d;
    struct dirent *de;
    struct stat st;
    int total;
    char buffer[BUFFER_SIZE];

    d = opendir(path);
    if (d == NULL){
        perror("opendir");
        return 0;
    }
    
    total = 0;
    // Check each file in directory
    while ((de = readdir(d)) != NULL) {
        
        snprintf(buffer, sizeof(buffer), "%s/%s", path, de->d_name);
        int rc = lstat(buffer, &st);
        if (rc == -1) {
            perror("lstat error");
            return 1;
        }
        if (S_ISREG(st.st_mode)){
            total += st.st_size;    // If regular file, add size to total
        }
        else if (S_ISDIR(st.st_mode) && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..")!= 0) {
            total += getsize(buffer);   // recurse if directory
        }
    }
    // print
    closedir(d);
    printf( "%s: %d\n", path, total);
    return total;
}

