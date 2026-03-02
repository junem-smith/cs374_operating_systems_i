#include <pthread.h>
#include <unistd.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t my_cond = PTHREAD_COND_INITIALIZER;

int count = 0;

void *run1(void *arg)
{
    while (1){
        pthread_mutex_lock(&my_mutex);

        if (count>=5) {
            pthread_mutex_unlock(&my_mutex);
            break;
        }

        count++;
        printf("Thread 1: count is %d\n", count);
        pthread_cond_signal(&my_cond);
        pthread_mutex_unlock(&my_mutex);
        sleep(1);
    }
    
    return NULL;
}

void *run2(void *arg)
{
    pthread_mutex_lock(&my_mutex);

    while (count < 5) {
        pthread_cond_wait(&my_cond, &my_mutex);
        printf("Thread 2: count is %d\n", count);
    }

    pthread_mutex_unlock(&my_mutex);
    return NULL;
}


int main(void)
{
    pthread_t t1;
    pthread_t t2;


    pthread_create(&t1, NULL, run1, NULL);
    pthread_create(&t2, NULL, run2, NULL);
    

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

}