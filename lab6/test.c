#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>
void * fun1()
{
	while(true){
		 printf("hi its fun 1\n");
		sleep(1);
	}
	pthread_exit(NULL);
}
void * fun2()
{
	while(true)
	{
		printf("hi its fun2\n");
		sleep(1);
	}
	pthread_exit(NULL);
}
int main()
{
	pthread_t t1,t2;
	pthread_create(&t1,NULL,fun1,NULL);
	pthread_create(&t2,NULL,fun2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}
