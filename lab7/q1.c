#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 

pthread_mutex_t forks[N];

void *philosopher(void *arg) {
    int philosopher_id = *((int *)arg);
    int right_fork = philosopher_id;
    int left_fork = (philosopher_id + 1) % N;

    if (philosopher_id % 2 == 1) {
        pthread_mutex_lock(&forks[right_fork]);
        pthread_mutex_lock(&forks[left_fork]);
    } else {
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);
    }

    printf("Philosopher %d is eating\n", philosopher_id);
    sleep(2); 
    printf("Philosopher %d is done eating\n", philosopher_id);

    pthread_mutex_unlock(&forks[left_fork]);
    pthread_mutex_unlock(&forks[right_fork]);

    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[N];
    int philosopher_ids[N];

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
