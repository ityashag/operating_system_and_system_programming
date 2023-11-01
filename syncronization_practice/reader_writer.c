#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int data = 0, readers = 0;
sem_t mutex, wrt;

void *reader(void *arg) {
    sem_wait(&mutex);
    readers++;
    if (readers == 1) {
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    // Reading the shared data
    printf("Reader %d read data: %d\n", *((int *)arg), data);

    sem_wait(&mutex);
    readers--;
    if (readers == 0) {
        sem_post(&wrt);
    }
    sem_post(&mutex);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    sem_wait(&wrt);
    // Writing to the shared data
    data = data + 5;
    printf("Writer wrote data: %d\n", data);
    sem_post(&wrt);

    pthread_exit(NULL);
}

int main() {
    int i;
    pthread_t readers[5], writers[5];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)&i);
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    for (i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
