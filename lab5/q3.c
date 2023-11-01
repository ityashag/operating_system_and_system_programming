#include <stdio.h>
#include <stdbool.h>
int main()
{
	int n_pro;
	printf("round robin cpu scheduling algo\n");
	int time_q;

	printf("Enter the time quantum :  ");
	scanf("%d",&time_q);
	printf("Enter the number of process : ");
	scanf("%d",&n_pro);

	int id[n_pro];
	int bust[n_pro];

	for(int i=0;i<n_pro;i++)
	{
		printf("Enter the bust time of process id %d : ",i);
		int b;
		scanf("%d",&b);
		bust[i]=b;
		id[i]=i;
	}

	int  time = 0;
	int r_bust[n_pro];

	for(int i=0;i<n_pro;i++)
	{
		 r_bust[i]=bust[i];
	}

	printf("GANT CHART \n|%d| ",time);

	bool flag = true;

	while(flag)
	{
		flag = false;
		for(int i=0;i<n_pro;i++)
		{
			if(r_bust[i]>0)
			{
				if(r_bust[i]<time_q)
				{
					time += r_bust[i];
					printf(" process_id=%d |%d| ",id[i],time);
					r_bust[i] -=r_bust[i];
				}
				else
				{
					time +=time_q;
					printf(" process_id=%d |%d| ",id[i],time);
					r_bust[i] -= time_q;
				}
				flag = true;
			}
		}
	}
}
