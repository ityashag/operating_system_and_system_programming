#include <stdio.h>
#include <unistd.h>
  
int main()
{
	printf("pid_ %d\n",getpid());
     if (fork() && (!fork())) {
	printf("pid _ %d\n",getpid());
        if (fork() || fork()) {
		printf("HI I AN INSIDE %d/n",getpid());
 
            fork();
        }
    }

    printf("pid %d , 2\n",getpid());
    return 0;
}
