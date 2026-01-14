#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int main(void){
    struct dirent *de;
    DIR *d = opendir(de->d_name);
    if (d == NULL){
        perror("opendir");
        return closedir(de->d_name);
    }
    d = readdir(d);
    
}

