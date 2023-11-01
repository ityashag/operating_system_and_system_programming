#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t resource1_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource2_mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *arg) {
    printf("Thread 1: Attempting to acquire Resource 1\n");
    pthread_mutex_lock(&resource1_mutex);
    printf("Thread 1: Acquired Resource 1\n");

    sleep(2);

    printf("Thread 1: Attempting to acquire Resource 2\n");
    pthread_mutex_lock(&resource2_mutex);
    printf("Thread 1: Acquired Resource 2\n");



    pthread_mutex_unlock(&resource1_mutex);
    pthread_mutex_unlock(&resource2_mutex);
    printf("Thread 1: Released Resources\n");

    pthread_exit(NULL);
}

void *thread2(void *arg) {
    printf("Thread 2: Attempting to acquire Resource 2\n");
    pthread_mutex_lock(&resource2_mutex);
    printf("Thread 2: Acquired Resource 2\n");

    sleep(1);

    printf("Thread 2: Attempting to acquire Resource 1\n");
    pthread_mutex_lock(&resource1_mutex);
    printf("Thread 2: Acquired Resource 1\n");


    pthread_mutex_unlock(&resource2_mutex);
    pthread_mutex_unlock(&resource1_mutex);
    printf("Thread 2: Released Resources\n");

    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main: Threads have finished\n");

    return 0;
}
