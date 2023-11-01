#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CHAIRS 5 // Number of waiting room chairs

sem_t customers; // Number of waiting customers
sem_t barber;    // Barber semaphore
sem_t mutex;     // Mutex to protect critical sections

int waiting = 0; // Number of customers waiting

void *barber_thread(void *arg) {
    while (1) {
        sem_wait(&customers); // Wait for a customer to arrive
        sem_wait(&mutex);     // Protect the waiting variable
        waiting--;
        sem_post(&barber);    // Signal that the barber is ready

        sem_post(&mutex);     // Release the mutex

        // Cut hair
        printf("Barber is cutting hair\n");
        sleep(2); // Simulate cutting hair

        sem_post(&barber);    // Signal that the haircut is done
    }
}

void *customer_thread(void *arg) {
    int id = *((int *)arg);

    sem_wait(&mutex); // Protect the waiting variable

    if (waiting < NUM_CHAIRS) {
        waiting++;
        printf("Customer %d is waiting\n", id);
        sem_post(&customers); // Signal to the barber that there's a customer
        sem_post(&mutex);     // Release the mutex

        sem_wait(&barber);    // Wait for the barber to finish cutting hair
        printf("Customer %d is getting a haircut\n", id);
        sem_wait(&barber);    // Wait for the barber to finish

        printf("Customer %d has left\n", id);
    } else {
        printf("Customer %d has left (no chairs available)\n", id);
        sem_post(&mutex); // Release the mutex
    }
}

int main() {
    pthread_t barber_tid, customer_tid;
    int customer_ids[NUM_CHAIRS];

    sem_init(&customers, 0, 0);
    sem_init(&barber, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&barber_tid, NULL, barber_thread, NULL);

    for (int i = 0; i < NUM_CHAIRS; i++) {
        customer_ids[i] = i + 1;
        pthread_create(&customer_tid, NULL, customer_thread, &customer_ids[i]);
        sleep(1); // Simulate arrival of customers at different times
    }

    pthread_join(barber_tid, NULL);

    sem_destroy(&customers);
    sem_destroy(&barber);
    sem_destroy(&mutex);

    return 0;
}
