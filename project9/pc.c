#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include "eventbuf.h"

struct eventbuf *ebuf;

sem_t *mutex;
sem_t *items;
sem_t *spaces;

int events;

sem_t *sem_open_temp(const char *name, int value)
{    sem_t *sem;

    // Create the semaphore
    if ((sem = sem_open(name, O_CREAT, 0600, value)) == SEM_FAILED)
        return SEM_FAILED;

    // Unlink it so it will go away after this process exits
    if (sem_unlink(name) == -1) {
        sem_close(sem);
        return SEM_FAILED;
    }

    return sem;
}

void *p_run(void *args)
{
    int *params = args;
    int thread_id = params[0];
    
    // TODO
    for(int i = 0; i < events; i++)
    {
        int event = thread_id * 100 + i;
        
        sem_wait(spaces);
        sem_wait(mutex);
        
        eventbuf_add(ebuf, event);
        printf("P%d: adding event %d\n", thread_id, event);

        sem_post(mutex);
        sem_post(items);

    }
    printf("P%d: exiting\n", thread_id);
    return NULL;
}
void *c_run(void *args)
{
    int *params = args;
    int thread_id = params[0];
    
    while(1)
    {
        sem_wait(items);
        sem_wait(mutex);
        
        if(eventbuf_empty(ebuf))
        {
            sem_post(mutex);
            break;
        }
        
        int event = eventbuf_get(ebuf);
        printf("C%d: got event %d\n", thread_id, event);

        sem_post(mutex);
        sem_post(spaces);

    }
    printf("C%d: exiting\n", thread_id);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 5) {
        fprintf(stderr, "usage: pc nproducers nconsumers events max_outstanding_events\n");
        exit(1);
    }

    // Parse the command line
    int p = atoi(argv[1]);
    int c = atoi(argv[2]);
    events = atoi(argv[3]);
    int outs = atoi(argv[4]);

    // Create the event buffer
    ebuf = eventbuf_create();

    mutex = sem_open_temp("sem_mutex", 1);
    items = sem_open_temp("sem_items", 0);
    spaces = sem_open_temp("sem_spaces", outs);

    pthread_t consumer[c], producer[p];
    int c_id[c], p_id[p];
    
    for(int i=0; i<p; i++){
        p_id[i] = i;
        pthread_create(&producer[i], NULL, p_run, &p_id[i]);
    }
    for(int j=0; j<c; j++){
        c_id[j] = j;
        pthread_create(&consumer[j], NULL, c_run, &c_id[j]);
    }


    for(int i=0; i<p; i++)
        pthread_join(producer[i], NULL);
    
    for(int i = 0; i < c; i++)
        sem_post(items);
    for(int j=0; j<c; j++)
        pthread_join(consumer[j], NULL);
    

    eventbuf_free(ebuf);

    sem_close(mutex);
    sem_close(items);
    sem_close(spaces);


}


