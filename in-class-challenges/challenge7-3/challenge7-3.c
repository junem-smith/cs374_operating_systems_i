
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 4

int *run(void *args)
{
    void(args);
    puts("running");
    return NULL;

}

int main(void)
{

    puts("parent: hello!");

    pthread_t thread[THREAD_COUNT];

    for (int i = 0; i<THREAD_COUNT; i++) {
        pthread_create(thread + i, NULL, run, NULL);	// Pointer arithmetic
    }
    for (int i = 0; i<THREAD_COUNT; i++) {
        pthread_join(thread[i], NULL);
    }

    puts("parent: goodbye!");   // child won't print unless parent is doing something. When the main thread dies, child threads die also.
    
}




