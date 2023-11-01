#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
int main()
{
    if (fork() && (!fork())) {
        printf("hi");
    }
    printf("ppid %d\n",getppid());
    sleep(10);
}
