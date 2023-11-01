#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t mutex;
pthread_cond_t condition;
int data_ready = 0;

void *producer(void *arg) {
   while(1){
    pthread_mutex_lock(&mutex);
    // Produce data
    data_ready = 1;
    printf("Producer: Data is ready.\n");
    sleep(2);
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&mutex);
    sleep(2);
    }
}

void *consumer(void *arg) {
   while(1){
    pthread_mutex_lock(&mutex);
    while (data_ready == 0) {
        printf("Consumer: Waiting for data...\n");
        pthread_cond_wait(&condition, &mutex);
    }
    // Consume data
    printf("Consumer: Data consumed.\n");
    data_ready = 0;
    sleep(2);
    pthread_mutex_unlock(&mutex);
    sleep(2);}
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    return 0;
}
