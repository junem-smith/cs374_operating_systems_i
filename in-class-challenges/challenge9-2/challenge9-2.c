#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t my_cond = PTHREAD_COND_INITIALIZER;

int count;

void *run1(void *arg)
{
    (void)arg;

    sleep(1);
    pthread_mutex_lock(&my_mutex);
    while (count > 3) {
        pthread_cond_wait(&my_cond, &my_mutex);
    }
    printf("Halfway there!\n");
    pthread_mutex_unlock(&my_mutex);

    return NULL;
}

void *run2(void *arg)
{
    (void)arg;
    pthread_mutex_lock(&my_mutex);

    while (count > 0) {
        pthread_cond_wait(&my_cond, &my_mutex);
    }
    printf("Liftoff!\n");

    pthread_mutex_unlock(&my_mutex);
    return NULL;
}


int main(void)
{
    pthread_t t1, t2;
    count = 6;

    pthread_create(&t1, NULL, run1, NULL);
    pthread_create(&t2, NULL, run2, NULL);
    
    // loop, decrementing the value while it's greater than 0
        // Broadcast to all the waiting threads
        // Sleep 1 second between decrements
    // Tell threads to wake up
    while(count > 0) {
        printf("%d\n", count);
        count--;
        pthread_cond_broadcast(&my_cond);
        sleep(1);
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

}