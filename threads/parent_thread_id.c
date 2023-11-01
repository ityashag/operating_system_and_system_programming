#include<stdio.h>
#include<pthread.h>
void* fun(){
printf("hi%d\n",(int)pthread_self());
}
int main(){
pthread_t p;
printf("%d\n",(int)pthread_self());
pthread_create(&p,NULL,fun,NULL);
pthread_join(p,NULL);
printf("%d",(int)pthread_self());
}
