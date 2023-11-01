#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
void* fun(void* arg)
{
    int id = *((int*)arg);
    printf("Thread %d starting...\n", id);
    double sum = 0;
    for (double ii = 0; ii < 1000; ii++) {
        sum = sum + sin(ii) + tan(ii);
    }

    printf("Thread %d done, result %f\n", id, sum);
    return NULL;
}

int main()
{
    pthread_t t[4];
    for (int i = 0; i < 4; i++) {
        printf("MAIN: Creating thread %d\n", i);
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&t[i], NULL, fun, (void*)id);
    }

    for (int i = 0; i < 4; i++) {
        printf("Main: Completed join %d\n", i);
        pthread_join(t[i], NULL);
    }
   printf("Main completed. \n");
}

