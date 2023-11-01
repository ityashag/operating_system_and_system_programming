#include <stdio.h>

int main()
{
	int n_pro ;
	printf("priority cpu scheduling algo \n");
	printf("Enter the number of process : ");
	scanf("%d",&n_pro);

	int id[n_pro];
	int pri[n_pro];
	int bust[n_pro];

	for(int i=0;i<n_pro;i++)
	{
		printf("Enter the bust time and priority of process id %d : ",i);
		int b,p;
		scanf("%d%d",&b,&p);
		pri[i]=p;
		bust[i]=b;
		id[i]=i;
	}

	for(int i=0;i<n_pro-1;i++)
	{
		for(int j = i+1;j<n_pro;j++)
		{
			if(pri[i]<pri[j])
			{
				int temp_b = bust[i] , temp_p = pri[i],temp_i=id[i];
				bust[i] = bust[j]; 
				pri[i]=pri[j];
				id[i] = id[j];

				bust[j] = temp_b;
				pri[j]=temp_p;
				id[j]=temp_i;
			}
		}
	}
	int  time = 0;
	printf("GANT CHART \n|%d| ",time);
	for(int i = 0;i<n_pro;i++)
	{
		time += bust[i];
		printf(" process_id=%d |%d| ",id[i],time);
	}
	printf("\n");
	 time = 0;
	printf("processid  turn_around_time waiting_time\n");
	for(int i=0;i<n_pro;i++)
	{
		printf("       %d                 %d           %d\n",id[i],time+bust[i],time);
		time+=bust[i];
	}
}
