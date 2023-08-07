//Program to impelement leaky bucket algorithm

#include <stdio.h>

struct proc
{
	int at,size;
};

typedef struct proc proc;


void main()
{
	int n;
	printf("\nEnter the number of processes:");
	scanf("%d",&n);
	
	proc packet[n];
	
	int sum=0;
	printf("\nEnter the arrival time and packet size in order:\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d %d",&packet[i].at,&packet[i].size);
		sum+=packet[i].size;
	}
	
	int bsize;
	printf("\nEnter the bucket size:");
	scanf("%d",&bsize);
	
	int stored=0,time=1,i=0;
	
	int out;
	printf("\nEnter the output rate:");
	scanf("%d",&out);
	
	while(sum!=0)
	{
		printf("\nAT TIME %d\n",time);
		if(time==packet[i].at)
		{
			if(packet[i].size>=bsize-stored)
			{
				sum-=packet[i].size;
				printf("\nPacket disgarded %d\n",i+1);
			}
			else
				stored+=packet[i].size;
			i++;
		}
			
		
		if(stored==0)
		{
			printf("\nNo packets to transmit\n");
			printf("\n0 bytes in the bucket\n");
		}
				
		else if(stored<out)
		{
					
			printf("\n%d packets transmitted\n",stored);
			sum-=stored;
			stored=0;
			printf("\n%d bytes in the bucket\n",stored);
		}
				
		else
		{
			printf("\n%d packets transmitted\n",out);
			stored-=out;
			sum-=out;
			printf("\n%d bytes in the bucket\n",stored);
		}
		time++;
	}
	
}
		
	
