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
	for(int i=0;i<*n;i++)
	{
		for(int j=0;j<*n;j++)
		{
			if(p[i].ari<p[j].ari)
			{
				struct process t  = p[i];
				p[i] = p[j];
				p[j] = t;
			}
		}
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

void * prior (void * arg)
{
	for(int i=0;i<*n;i++)
	{
		for(int j=0;j<*n;j++)
		{
			if(p[i].ari<p[j].ari)
			{
				struct process t  = p[i];
				p[i] = p[j];
				p[j] = t;
			}
		}
	}

	int time =0;
	int count =0;
	printf("GANT CHART\n|%d| ",time);
	while(count<*n)
	{
		int flag =0;
		int index = 0;
		for(int i=0;i<*n;i++)
		{
			if(p[i].p_ari<=time && p[i].r_bust>0)
			{
				p[i].avl=1;
				flag=1;
				index = i;
			}
			else p[i].avl=0;
		}
		if(flag==1)
		{
			
			for(int i=0;i<*n;i++)
			{
				if(p[i].avl==1 && p[index].pri<p[i].pri)
				{
					index = i;
				}
			}
			
			time +=1;
			printf(" process %d |%d| ",p[index].id,time);
			p[index].r_bust-=1;
			if(p[index].r_bust==0)
			{
				count++;
				p[index].ca=time;
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

void * round_robin(void * arg)
{
	for(int i=0;i<*n;i++)
	{
		for(int j=0;j<*n;j++)
		{
			if(p[i].ari<p[j].ari)
			{
				struct process t  = p[i];
				p[i] = p[j];
				p[j] = t;
			}
		}
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
					if(p[i].r_bust<=(*t1))
					{
						time+=p[i].r_bust;
						printf(" process %d |%d| ",p[i].id,time);
						p[i].r_bust=0;
						p[i].ca=time;
						count++;
					}
					else
					{
						time+=(*t1);
						printf(" process %d |%d| ",p[i].id,time);
						p[i].r_bust-=(*t1);
						p[i].p_ari=time;
					}
				}
				
			}
			
			for(int i=0;i<*n;i++)
			{
				for(int j=0;j<*n;j++)
				{
					if((p[i].p_ari<p[j].p_ari) || (p[i].p_ari==p[j].p_ari && p[i].ari<p[j].ari))
					{
						struct process t  = p[i];
						p[i] = p[j];
						p[j] = t;
					}

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


void * display(void *arr)
{
	printf("pid at bt ca ta wt\n");
	for(int i=0;i<*n;i++)
	{
		for(int j=0;j<*n;j++)
		{
			if(p[i].id<p[j].id)
			{
				struct process l = p[i];
				p[i] = p[j];
				p[j] = l;
			}
		}
	}
	for(int i=0;i<*n;i++)
	{
		printf(" %d  %d %d %d %d %d\n",p[i].id,p[i].ari,p[i].bust,p[i].ca,p[i].ca-p[i].ari,p[i].ca-p[i].ari-p[i].bust);
	}
}

int main()
{
	n = malloc(sizeof(int));
	printf("ENTER NUMBER OF PROCESS : ");
	scanf("%d",n);
	p = malloc(sizeof(struct process)*(*n));
	/*for(int i=0;i<*n;i++)
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
	display(NULL);*/
	
	/*for(int i=0;i<*n;i++)
	{
		int b,a,pr;
		printf("ENTER PROCESS %d BUST TIME , ARIVAL TIME  AND PRIORITY : ",i);
		scanf("%d%d%d",&b,&a,&pr);
		p[i].bust=b;
		p[i].ca;
		p[i].ari=a;
		p[i].avl=0;
		p[i].id=i;
		p[i].turn=0;
		p[i].r_bust=b;
		p[i].p_ari=a;
		p[i].pri=pr;
	}
	prior(NULL);
	display(NULL);
	*/
	 t1 = malloc(sizeof(int));
	 printf("ENTER THE TIME Q : ");
	 scanf("%d",t1);
	 pthread_t tt1,tt2;
	for(int i=0;i<*n;i++)
	{
		int b,a;
		printf("ENTER PROCESS %d BUST TIME AND ARIVAL TIME :",i);
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
	pthread_create(&tt1,NULL,round_robin,NULL);
	pthread_join(tt1,NULL);
	pthread_create(&tt2,NULL,display,NULL);
	pthread_join(tt2,NULL);
	
	
//	printf("ENTER THE TIME QUANTUM FOR QUEUE 1 : ");
//	scanf("%d",t1);
//	printf("ENTER THE TIME QUANTUM FOR QUEUE 2 : ");
//	scanf("%d",t2);
//	mlfq();
}
