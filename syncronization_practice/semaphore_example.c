#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

sem_t my_semaphore;
int shared_resource = 0;
void *thread_function(void *id) {
    long tid = (long)id;

    sem_wait(&my_semaphore); // Decrement semaphore value, block if currently zero
    printf("Thread %ld enters the critical section.\n", tid);
    // Critical section
    shared_resource +=1;
    printf("Thread %ld leaves the critical section, shared_resource value = %d .\n", tid,shared_resource);
    sem_post(&my_semaphore); // Increment semaphore value

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    sem_init(&my_semaphore, 0, 1);

    long i;
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void *)i);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("The final shared_resource value = %d ",shared_resource);
    sem_destroy(&my_semaphore);

    return 0;
}
