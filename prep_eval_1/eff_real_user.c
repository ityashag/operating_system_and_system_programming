#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
int main()
{
	printf("%d\n",getuid());
	printf("%d\n",geteuid());
	printf("%d\n",nice(0));
	printf("%d\n",getpid());
	printf("%d\n",getppid());
	int a = fork();
	if(a==0)
	{
		printf("#%d\n",getppid());
		sleep(10);
		printf("#%d\n",getppid());
	}
}
