#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct process{
	int bust;
	int ari;
	int avl;
	int id;
	int r_bust;
	int p_ari;
	int turn;
	int ca;
	int pri;
};



int * n;
int*t1;
int*t2;
struct process *p;

void * fcfs (void * arg)
{
	for(int i=0;i<(*n)-1;i++)
	{
		for(int j=i;j<*n;j++)
		{
			if(p[i].ari<p[j].ari)
			{
				struct process t  = p[i];
				p[i] = p[j];
				p[j] = t;
			}
		}
	}
	for(int i=0;i<*n;i++)
	{
		printf("%d\n",p[i].id);
	}

	int time =0;
	int count =0;
	printf("GANT CHART\n|%d| ",time);
	while(count<*n)
	{
		int flag =0;
		for(int i=0;i<*n;i++)
		{
			if(p[i].p_ari<=time && p[i].r_bust>0)
			{
				p[i].avl=1;
				flag=1;
			}
			else p[i].avl=0;
		}
		if(flag==1)
		{
			for(int i=0;i<*n;i++)
			{
				if(p[i].avl==1)
				{
					time+=p[i].r_bust;
					printf(" process %d |%d| ",p[i].id,time);
					p[i].r_bust-=p[i].r_bust;
					p[i].ca=time;
					count++;
				}
			}
		}
		else
		{
			time+=1;
			printf(" |%d| ",time);
		}
	}
	printf("\n");

}

int main()
{
	n = malloc(sizeof(int));
	printf("ENTER NUMBER OF PROCESS : ");
	scanf("%d",n);
	p = malloc(sizeof(struct process)*(*n));
	for(int i=0;i<*n;i++)
	{
		int b,a;
		printf("ENTER PROCESS %d BUST TIME AND ARIVAL TIME : ",i);
		scanf("%d%d",&b,&a);
		p[i].bust=b;
		p[i].ca;
		p[i].ari=a;
		p[i].avl=0;
		p[i].id=i;
		p[i].turn=0;
		p[i].r_bust=b;
		p[i].p_ari=a;
	}
	fcfs(NULL);

}
