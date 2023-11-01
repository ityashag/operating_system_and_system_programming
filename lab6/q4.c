#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
int account = 1000;
bool can_withdraw = false;

void * deposite (void * a)
{
	int* amount = (int*) a;
	account+=(*amount);
	if(account>1000) can_withdraw = true;
	else can_withdraw = false;
}

void * withdraw (void  *a)
{
	if(can_withdraw){
	int* amount = (int*)a;
	account-=(*amount);
	}
}

int main()
{
	int* d_am= malloc(sizeof(int));
	*d_am=150;
	int* w_am =malloc(sizeof(int));
	*w_am =120;
	pthread_t t1,t2;
	pthread_create(&t1,NULL,deposite,(void *)d_am);
	pthread_create(&t2,NULL,withdraw,(void *)w_am);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("FINAL AMOUNT IN ACCCOUNT : %d\n",account);
}
