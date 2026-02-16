#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int *run(void *args)
{
    void(args);
    puts("child: hello!");
    puts("child: goodbye!");
    return NULL;

}

int main(void)
{
    // Opaque type
    pthread_t t1; // thread identifier, a la process id

    puts("parent: hello!");
    // create a new thread
    pthread_create(&t1, NULL, run, NULL);

    // Wait for the child thread to complete.
    pthread_join(t1, NULL);

    puts("parent: goodbye!");   // child won't print unless parent is doing something. When the main thread dies, child threads die also.
    
}