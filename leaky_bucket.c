//Program to implement leaky bucket congestion control algorithm

#include <stdio.h>

struct packet{
	int at,size;
};


void main()
{
	int n,sum=0;
	printf("\nEnter the number of packets:");
	scanf("%d",&n);
	
	
	struct packet pac[n];
	
	printf("\nEnter the packets in order of their arrival time:\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d %d",&pac[i].at,&pac[i].size);
		sum+=pac[i].size;
	}
		
	int bsize;
	printf("\nEnter the bucket size:");
	scanf("%d",&bsize);
	
	int out;
	printf("\nEnter the output rate:");
	scanf("%d",&out);

	int stored=0,i=0,fin=0;
	int time=1;
	
	while(1)
	{	
		printf("\n\n\nAT TIME %d",time);
		if(time==pac[i].at)
		{
			if(pac[i].size>bsize-stored)
			{
				printf("\nPacket discarded");
				sum-=pac[i].size;
				fin++;
			}
			
			else
			{
				stored+=pac[i].size;
				printf("\n%d bytes packet inserted",pac[i].size);
				if(stored==0)
				{
					printf("\nNo packets to transmit");
					printf("\nPackets in the bucket is 0 bytes");
				}
				
				else if(stored<=out)
				{
					printf("\n%d bytes packets transmitted",stored);
					sum-=stored;
					stored=0;
					printf("\nPackets in the bucket is 0 bytes");
					fin++;
				}
				else
				{
					printf("\n%d bytes packets transmitted",out);
					stored-=out;
					sum-=out;
					printf("\nPackets in the bucket is %d bytes",stored);
				}
				
			}
			i++;
			time++;
		}
		
		else
		{
			if(stored==0)
			{
				printf("\nNo packets to transmit");
				printf("\nPackets in the bucket is 0 bytes");
			}
			
			else if(stored<=out)
			{
				printf("\n%d bytes packets transmitted",stored);
				sum-=stored;
				stored=0;
				printf("\nPackets in the bucket is 0 bytes");
				fin++;
			}
			else
			{
				printf("\n%d bytes packets transmitted",out);
				stored-=out;
				sum-=out;
				printf("\nPackets in the bucket is %d bytes",stored);
			}
				
			time++;
		}
		
		if(sum==0)
			break;
		
		
	}	
	
	printf("\n");	
	

}
