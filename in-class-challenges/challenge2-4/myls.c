#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int main(void){
    DIR *d;
    struct dirent *de;

    d = opendir(".");
    if (d == NULL){
        perror("opendir");
        return closedir(de->d_name);
    }
    d = readdir(d);

    while ((de = readdir(d)) != NULL) {
        printf("%s\n", de->d_name);
    }

    closedir(d);
    return 0;
    
}

