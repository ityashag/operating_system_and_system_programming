#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 
#define NUM_PRODUCERS 6 
#define NUM_CONSUMERS 6 

int buffer[BUFFER_SIZE];
int count = 0; 
int in = 0; 
int out = 0;
int item = 0;
pthread_mutex_t mutex; 
sem_t full; 
sem_t empty;

void *producer(void *arg) {
    while (1) { 
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
	item ++;
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        count++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1); 
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); 
        sleep(2);
    }
}

int main() {
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
