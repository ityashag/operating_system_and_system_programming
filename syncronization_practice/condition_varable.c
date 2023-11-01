#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t condition_variable;
int shared_data = 0;

void *thread_function(void *id) {
    printf("Thread waiting for condition to be signaled.\n");
    pthread_cond_wait(&condition_variable, &mutex);
    printf("Thread exiting.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition_variable, NULL);

    pthread_create(&thread, NULL, thread_function, NULL);

    pthread_mutex_lock(&mutex);
    while (shared_data < 10) {
        shared_data++;
        if (shared_data == 5) {
            printf("Signaling condition variable.\n");
            pthread_cond_signal(&condition_variable);
        }
        printf("Incrementing shared data to: %d\n", shared_data);
    }
    pthread_mutex_unlock(&mutex);

    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition_variable);

    return 0;
}
