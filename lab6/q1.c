
#include <stdio.h>
#include <pthread.h>

void * fun ()
{
	printf("HELLO WORLD!\n");
	pthread_exit(NULL);
}
int main()
{
	pthread_t p[5];
	for(int i=0;i<5;i++)
	{
		pthread_create(&p[i],NULL,fun,NULL);
	}
	for(int i=0;i<5;i++)
	{
		pthread_join(p[i],NULL);
	}
}
