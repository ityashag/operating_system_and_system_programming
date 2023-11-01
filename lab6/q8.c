#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int s =0;
void * inc ()
{
	int y = s;
	y++;
	sleep(1);
	s=y;
}

void * dec()
{
	int x = s;
	x--;
	sleep(1);
	s=x;
}

int main()
{
	pthread_t t1,t2;
	pthread_create(&t1,NULL,inc,NULL);
	pthread_create(&t2,NULL,dec,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("final value of s : %d\n",s);
}
