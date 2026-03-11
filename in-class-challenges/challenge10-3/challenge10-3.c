#include <stdio.h>

void f1(void) 
{
    puts("f1  Called");
}

void f2(void) 
{
    puts("f2 Called");
}

int main(void) {
    void (*runf[5])(void) = {f1, f2, f1, f2, f1};

    for(int i = 0; i<5; i++){
        runf[i]();
    }

}

