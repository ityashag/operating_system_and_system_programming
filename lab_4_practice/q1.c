#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
int main()
{
	char * m1 = "it's from p1.\0";
	char * m2 = "addon by p2.\0";
	char buffer[100];
	int pipe1[2],pipe2[2];
	pid_t f;
	pipe(pipe1);
	pipe(pipe2);
	f=fork();
	if(f==0)
	{
		close(pipe2[0]);
		close(pipe1[1]);
		write(pipe2[1],m1,13);
		read(pipe1[0],buffer,sizeof(buffer));
		printf("%s\n",buffer);
	}
	else if(f>0)
	{
		close(pipe2[1]);
		close(pipe1[0]);
		read(pipe2[0],buffer,sizeof(buffer));
		for(int i=0;i<100;i++)
		{
			if(buffer[i]=='.')
			{
				i++;
				for(int j=0;m2[j]!='.';j++)
				{
					buffer[i++]=m2[j];
				}
				buffer[i]='\0';
				i=101;
			}
		}
		write(pipe1[1],buffer,sizeof(buffer));
	}

}
