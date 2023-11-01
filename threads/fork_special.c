#include<stdio.h>
#include<unistd.h>
int main(){


if(fork()||fork()&&fork()) fork();
printf("%d\n",getpid());
}
