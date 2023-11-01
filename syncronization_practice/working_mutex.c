#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int shared_resource = 0;
pthread_mutex_t mutex;

void *thread_function(void *id) {
    long tid = (long)id;

    pthread_mutex_lock(&mutex); // Lock the mutex before accessing the shared resource
    printf("Thread %ld accessing the shared resource.\n", tid);
    shared_resource += 1; // Modify the shared resource
    printf("Shared resource value after increment: %d\n", shared_resource);
    pthread_mutex_unlock(&mutex); // Unlock the mutex after accessing the shared resource

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    long i;
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void *)i);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    printf("Final value of shared resource: %d\n", shared_resource);

    return 0;
}
