#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

#define NUM_THREADS 3
#define TCOUNT 10
#define COUNT_LIMIT 12

atomic_int count = ATOMIC_VAR_INIT(0);

void *inc_count(void *t) {
    int my_id = *((int *)t);

    for (int i = 0; i < TCOUNT; i++) {
        atomic_fetch_add(&count, 1);

        // Check if the count has reached the limit
        if (atomic_load(&count) >= COUNT_LIMIT) {
            printf("inc_count thread %d: count = %d. Signaling the waiting thread.\n", my_id, atomic_load(&count));
            atomic_store(&count, 0); // Reset count
        }

        printf("inc_count thread %d: count = %d.\n", my_id, atomic_load(&count));

    }
    pthread_exit(NULL);
}

void *watch_count(void *t) {
    int my_id = *((int *)t);

    while (atomic_load(&count) < TCOUNT * 2) {
        // Watch the value of count
        printf("watch_count thread %d: count = %d. Waiting...\n", my_id, atomic_load(&count));

        // Check if the count has reached the limit
        if (atomic_load(&count) >= COUNT_LIMIT) {
            printf("watch_count thread %d: count = %d. Awakened!\n", my_id, atomic_load(&count));
            atomic_store(&count, 0); // Reset count
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {0, 1, 2};

    // Create threads
    pthread_create(&threads[0], NULL, inc_count, &thread_ids[0]);
    pthread_create(&threads[1], NULL, inc_count, &thread_ids[1]);
    pthread_create(&threads[2], NULL, watch_count, &thread_ids[2]);

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final count = %d\n", atomic_load(&count));
    pthread_exit(NULL);

    return 0;
}
