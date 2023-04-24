//Program to implement server side TCP

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h> 

int cnt=0;

int main()
{
	int socket_desc,client_size,client_sock;
	FILE* f1;
	struct sockaddr_in client_addr,server_addr;
	char client_msg[4096],server_msg[4096];
	int arr[10];
	
	for(int i=0;i<10;i++)
		arr[i]=0;
		
	
	//Cleaning the buffers
	memset(&client_msg,'\0',sizeof(client_msg));
	memset(&server_msg,'\0',sizeof(server_msg));
	
	//creating the socket
	socket_desc=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	if(socket_desc<0)
	{
		printf("Socket creation unsuccessful\n");
		return(-1);
	}
	
	printf("Socket created successfully\n");
	pid_t child;
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2007);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//binding
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Couldn't bind to the port\n");
		return(-1);
	}
	
	printf("Done with binding\n");
	
	
	//listening for client
	
	if(listen(socket_desc,10)<0)
	{
		printf("Listening unsuccessful\n");
		return(-1);
	}
	
	printf("Listening for incoming connections\n");
	
	client_size=sizeof(client_addr);
	
	//Accepting the connection
	client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
	
	if(client_sock<0)
	{
		printf("Cannot accept\n");
		return(-1);
	}
	
	printf("Client connected at ip:%s and port:%i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	
	int count=1,no=1;
	
	//Recieve clients message
	while(1)
	{
		memset(&client_msg,'\0',sizeof(client_msg));
		memset(&server_msg,'\0',sizeof(server_msg));
	
		if(recv(client_sock,client_msg,sizeof(client_msg),0)<0)
		{
			printf("Couldn't recieve the Clients message\n");
			return(-1);
		}
		
		printf("Message recieved from the client is:%s\n",client_msg);
		
		
		int num=client_msg[0]-'0';
		
		if(count==no+2)
		{
		
			strcpy(server_msg,"NACK");
			snprintf(server_msg+strlen(server_msg),2,"%d",no);
			
			if(send(client_sock,server_msg,sizeof(server_msg),0)<0)
			{
				printf("Couldn't Send Servers message\n");
				return(-1);
			}
		
		}
		
		if(count!=no)
		{
			arr[num]=1;
			strcpy(server_msg,"ACK");
			snprintf(server_msg+strlen(server_msg),2,"%d",num);
			
			if(send(client_sock,server_msg,sizeof(server_msg),0)<0)
			{
				printf("Couldn't Send Servers message\n");
				return(-1);
			}
		
		}
		
		else
		{
			strcpy(server_msg,"nil");
			if(send(client_sock,server_msg,sizeof(server_msg),0)<0)
			{
				printf("Couldn't Send Servers message\n");
				return(-1);
			}
		
		}
		
		count++;
	}
	
	//Closing the socket
	
	close(client_sock);
	close(socket_desc);
	return(0);
}
	
	



