//Program to search in an array using UDP server

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int search(int arr[],int num,int key)
{
	int low=0,high=num-1;
	
	while(low<=high)
	{
		int mid=(low+high)/2;
		
		if(arr[mid]==key)
			return(mid);

		else if(arr[mid]>key)
			high=mid-1;
		else
			low=mid+1;
	}
	
	return(-1);
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

		int key;
		if(recvfrom(socket_desc,&key,sizeof(key),0,(struct sockaddr*)&client_addr,&client_size)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}

		int index=search(arr,num,key);
		
		if(sendto(socket_desc,&index,sizeof(index),0,(struct sockaddr*)&client_addr,sizeof(client_addr))<0)
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
