
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL); // Disable thread cancellation
    int i;
    for (i = 0; i < 5; i++) {
        printf("Thread is running... %d\n", i);
        sleep(1);
    }
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // Re-enable thread cancellation
    pthread_testcancel(); // Check for thread cancellation request
    for (i = 5; i < 10; i++) {
        printf("Thread is running... %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    sleep(2); // Sleep for 2 seconds to allow the thread to run

    // Request thread cancellation
    if (pthread_cancel(thread) != 0) {
        perror("pthread_cancel");
        return 1;
    }

    // Wait for the thread to finish
    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    printf("Thread has been canceled.\n");
    return 0;
}
