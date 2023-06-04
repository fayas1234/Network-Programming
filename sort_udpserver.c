//Program to sort an array using UDP server

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void sort(int arr[],int num)
{
	for(int i=0;i<num;i++)
	{
		for(int j=0;j<num-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

int main()
{
	int socket_desc;
	
	struct sockaddr_in client_addr,server_addr;
	
	char client_message[3];
	
	memset(client_message,'\0',sizeof(client_message));
	
	
	socket_desc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	if(socket_desc<0)
	{
		printf("\nCouldnot create the socket");
		return(-1);
	}
	printf("\nSocket created successfully");
	
	//Add the addresses
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2003);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("\nCould not bind");
		return(-1);
	}
	printf("\nBinding successfull");
	
	
	
	int client_size=sizeof(client_addr);
	
	while(1)
	{	
		int num;
			
		
		if(recvfrom(socket_desc,&num,sizeof(num),0,(struct sockaddr*)&client_addr,&client_size)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		
		
		printf("\nnumber of elements:%d",num);
		
		int arr[num];
		
		if(recvfrom(socket_desc,arr,sizeof(arr),0,(struct sockaddr*)&client_addr,&client_size)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}

		
		sort(arr,num);
		
		if(sendto(socket_desc,arr,sizeof(arr),0,(struct sockaddr*)&client_addr,sizeof(client_addr))<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		
		memset(client_message,'\0',sizeof(client_message));
		
		if(recvfrom(socket_desc,&client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_size)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
	
		printf("Response from client:%s\n",client_message);
		
		if(strcmp(client_message,"no")==0)
			break;
	}
	
	//close the sockets
	close(socket_desc);
		
}
