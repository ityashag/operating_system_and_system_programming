#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void *fun(void *in) {
    char **arr = (char **)in;
    printf("NAME : %s HALL_NO: %s  EID : %s BRANCH : %s\n", arr[0], arr[1],arr[2],arr[3]);
}

int main() {
    char **input = (char **)malloc(sizeof(char *) * 4);
    for (int i = 0; i < 4; i++) {
        input[i] = (char *)malloc(100);
    }

    input[0]="yash agarwal\0";
    input[1]="g6\0";
    input[2]="e123\0";
    input[3]="it\0";
    pthread_t t1, t2;
    pthread_create(&t1, NULL, fun, (void *)input);
    char **input2 = (char **)malloc(sizeof(char *) * 2);
    for (int i = 0; i < 2; i++) {
        input2[i] = (char *)malloc(100);
    }
    input2[0]="vipul verma\0";
    input2[1]="g6\0";
    input2[2]="e1235\0";
    input2[3]="it\0";
    pthread_create(&t2, NULL, fun, (void *)input2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

