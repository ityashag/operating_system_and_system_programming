#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int status;
	pid_t a = fork();
	if(a==0)
	{
		execlp("/bin/ls","ls","-lah",NULL);
		exit(1);
	}
	else  wait(&status);
	
}
