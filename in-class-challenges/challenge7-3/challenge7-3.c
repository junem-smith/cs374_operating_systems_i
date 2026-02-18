
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 4

int *run(void *args)
{
    int *id = args;
    puts("running from %d\n", id);
    return NULL;

}

int main(void)
{

    puts("parent: hello!");

    pthread_t thread[THREAD_COUNT];
    int thread_id[THREAD_COUNT];


    for (int i = 0; i<THREAD_COUNT; i++) {
        pthread_create(thread + i, NULL, run, thread_id + i);	// Pointer arithmetic
    }
    for (int i = 0; i<THREAD_COUNT; i++) {
        pthread_join(thread[i], NULL);
    }

    puts("parent: goodbye!");   // child won't print unless parent is doing something. When the main thread dies, child threads die also.
    
}




