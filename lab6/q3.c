#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int account = 0;

void * deposite (void * a)
{
	int* amount = (int*) a;
	for(int i=0;i<50;i++) account+=(*amount);
}

void * withdraw (void  *a)
{
	int* amount = (int*)a;
	for(int i=0;i<20;i++) account-=(*amount);
}

int main()
{
	int* d_am= malloc(sizeof(int));
	*d_am=50;
	int* w_am =malloc(sizeof(int));
	*w_am = 20;
	pthread_t t1,t2;
	pthread_create(&t1,NULL,deposite,(void *)d_am);
	pthread_create(&t2,NULL,withdraw,(void *)w_am);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("FINAL AMOUNT IN ACCCOUNT : %d",account);
}
