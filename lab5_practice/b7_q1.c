#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct process{
	int bust;
	int ari;
	int ca;
	int r_bust;
	int id;
	int turn;
	int avi;
	int p_ari;
};

int *n;
int *time_q;
struct process *p;

void * round_robin(void * arg)
{
	for(int i=0;i<*n;i++)
	{
		for(int j=0;j<*n;j++)
		{
			if(p[i].ari<p[j].ari)
			{
				struct process l = p[i];
				p[i]=p[j];
				p[j]=l;
			}
		}
	}

	int time = 0;
	printf("GANT CHART\n");
	printf("|%d| ",time);
	time =p[0].ari;
	printf("|%d|",time);
	int com = 0;
	while(com<*n)
	{
		int f = 0;
		for(int i=0;i<*n;i++)
		{
			if(p[i].r_bust>0 && p[i].p_ari<=time) {p[i].avi=1;f=1;}
			else p[i].avi=0;
		}
		if(f==1){
		for(int i=0;i<*n;i++)
		{
			if(p[i].avi==1)
			{
				if(p[i].r_bust<=p[i].turn+(*time_q))
				{
					time+=p[i].r_bust;
					printf(" process %d |%d| ",p[i].id,time);
					p[i].ca=time;
					p[i].turn+=1;
					p[i].r_bust-=p[i].r_bust;
					p[i].p_ari=time;
					com++;
				}
				else
				{
					time+=(p[i].turn+(*time_q));
					printf(" process %d |%d| ",p[i].id,time);
					p[i].turn+=1;
					p[i].p_ari=time;
					p[i].r_bust-=(p[i].turn-1+(*time_q));
				}
			}
		}
		for(int i=0;i<*n;i++) for(int j=0;j<*n;j++) if(p[i].p_ari<p[j].p_ari){struct process l = p[i]; p[i]=p[j];p[j]=l;}
		}
		else
		{
			time+=1;
			printf(" |%d| ",time);
		}
	}
	printf("\n");
}
void * display(void *arg)
{
	printf("pid bt at ca ta wt\n");
	for(int i=0;i<*n;i++)
	{
		for(int j=0;j<*n;j++)
		{
			if(p[i].id<p[j].id)
			{
				struct process l = p[i];
				p[i]=p[j];
				p[j]=l;
			}
		}
	}
	for(int i=0;i<*n;i++)
	{
		printf("%d  %d %d %d %d %d\n",p[i].id,p[i].bust,p[i].ari,p[i].ca,p[i].ca-p[i].ari,p[i].ca-p[i].ari-p[i].bust);
	}
}
int main()
{
	printf("ENTER THE NUMBER OF PROCESS : ");
	int nn;
	scanf("%d",&nn);
	n = malloc(sizeof(int));
	*n=nn;
	p = malloc(sizeof(struct process)*nn);
	int t;
	printf("ENTER THE TIME QUANTUM :");
	scanf("%d",&t);
	time_q = malloc(sizeof(int));
	*time_q = t;
	for(int i=0;i<*n;i++)
	{
		printf("ENTER THE PROCESS %d BUST TIME AND ARIVAL TIME",i);
		int b,a;
		scanf("%d%d",&b,&a);
		p[i].bust=b;
		p[i].ca=0;
		p[i].r_bust=b;
		p[i].ari=a;
		p[i].id=i;
		p[i].turn = 0;
		p[i].avi=0;
		p[i].p_ari=a;
	}
	pthread_t t1;
	pthread_create(&t1,NULL,round_robin,NULL);
	pthread_join(t1,NULL);
	pthread_t t2;
	sleep(10);
	pthread_create(&t2,NULL,display,NULL);
	pthread_join(t2,NULL);
}





