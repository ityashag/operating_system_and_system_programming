#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define QUEUE_SIZE 5 
#define FILENAME "string.txt" 

char queue[QUEUE_SIZE];
int front = 0, rear = 0;
int itemCount = 0;

pthread_mutex_t mutex;
pthread_cond_t not_full, not_empty;

void enqueue(char item) {
    queue[rear] = item;
    rear = (rear + 1) % QUEUE_SIZE;
    itemCount++;
}

char dequeue() {
    char item = queue[front];
    front = (front + 1) % QUEUE_SIZE;
    itemCount--;
    return item;
}

void *producer(void *arg) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char c;
    while ((c = fgetc(file)) != EOF) {
        pthread_mutex_lock(&mutex);
        while (itemCount == QUEUE_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }
        enqueue(c);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
    }

    fclose(file);
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (itemCount == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }
        char c = dequeue();
        printf("%c", c);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);

        if (c == '\n') {
            break;
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}
