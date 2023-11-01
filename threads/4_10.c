#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *t(void *arg)
{
    printf("\ntyt\n");
    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    int p = fork();

    if (p == 0)
    {
        fork();
        pthread_create(&tid, &attr, t, NULL);
        printf("tt\n");
        pthread_join(tid, NULL);
    }

    printf("hi\n");

    return 0;
}

