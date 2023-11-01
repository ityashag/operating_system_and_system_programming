#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

double *arr;

void * sq()
{
	arr = malloc(sizeof(double)*11);
	for(int i=0;i<=10;i++)
	{
		arr[i]=sqrt(i);
	}
}
int main()
{
	pthread_t t;
	pthread_create(&t,NULL,sq,NULL);
	printf("hi i am main \n");
	pthread_join(t,NULL);
	printf("array is ready\n");
	for(int i=0;i<=10;i++)
	{
		printf("%f ",arr[i]);
	}
	printf("\n");
}
