#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 

int main(void)
{
    int x = 12;
    float y = 3.14;
    char* s = "Hello, world!";

    printf("x is %d, y is %f\n", x, y);
    printf("%s\n", s);

    int mult;
    for (int i = 0; i < 5; i++){
        mult = i*5;
        printf("%d x 5 = %d\n", i, mult);
    }

}