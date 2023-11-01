#include <stdio.h>

int main()
{
	int n_pro;
	printf("ENTER THE NUMBER OF PROCESSES : ");
	scanf("%d",&n_pro);
	int bust[n_pro];
	int id[n_pro];
	
	// round robin
	int time_q;
	printf("ENTER THE TIME QUANTUM OF QUEUE 1:");
	scanf("%d",&time_q);
	for(int i=0;i<n_pro;i++)
	{
		printf("ENTER THE BUST TIME : ");
		int b;
		scanf("%d",&b);
		bust[i]=b;
		id[i]=i;
	}
	int time = 0;
	int r_bust[n_pro];
	int c_time[n_pro];
	for(int i=0;i<n_pro;i++) r_bust[i]=bust[i];
	printf("GANT CHART\n|%d| ",time);
	int flag = 0;
	for(int i=0;i<n_pro;i++)
	{
		if(r_bust[i]<=time_q)
		{
			time+=r_bust[i];
			printf(" process id = %d |%d| ",id[i],time);
			r_bust[i] -=r_bust[i];
			c_time[i] = time; 
		}
		else
		{
			time += time_q;
			printf(" process id = %d |%d| ",id[i],time);
			r_bust[i]-=time_q;
			c_time[i] = time;
			flag = 1;
		}
	}
	if(flag)
	{
		for(int i=0;i<n_pro;i++)
		{
			for(int j=i+1;j<n_pro;j++)
			{
				if(r_bust[i] == 0 || r_bust[i]>r_bust[j])
				{
					int temp_i = id[i] , temp_b = bust[i], temp_c = c_time[i],temp_r=r_bust[i];
					id[i]=id[j]; bust[i]=bust[j]; c_time[i] = c_time[j] ; r_bust[i]=r_bust[j];
					id[j] = temp_i; bust[j] = temp_b; c_time[j]=temp_c; r_bust[j]=temp_r;
				}
			}
		}
		for(int i=0;i<n_pro;i++)
		{
			if(r_bust[i]!=0)
			{
				time += r_bust[i];
				printf(" process id = %d |%d| ",id[i],time);
				r_bust[i]-=r_bust[i];
				c_time[i] = time;
			}
		}
	}
	printf("\nPid  TA  WT\n");
	for(int i=0;i<n_pro;i++)
	{
		printf("%d   %d  %d\n",id[i],c_time[i],c_time[i]-bust[i]);
	}
}
