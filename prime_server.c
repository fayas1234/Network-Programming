//Program to implement prime number using TCP server

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int isPrime(int num)
{
	if(num==1)
		return(0);
		
	if(num==2)
		return(1);
	
	
	for(int i=2;i<num;i++)
	{
		if(num%i==0)
			return(0);
	}
	
	return(1);
}

int main()
{
	int socket_desc,client_sock;
	
	char client_message[3];
	
	
	memset(client_message,'\0',sizeof(client_message));
	
	struct sockaddr_in client_addr,server_addr;
	
	socket_desc=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	if(socket_desc<0)
	{
		printf("Socket not created\n");
		return(-1);
	}
	printf("\nSocket created successfully");
	
	//Add addresses
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2005);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		printf("\nbinding unsuccessful");
		return(-1);
	}
	
	printf("\nBinding successfull");
	
	if(listen(socket_desc,1)<0)
	{
		printf("\nError while listening");
		return(-1);
	}
	
	printf("\nListening...");
	
	int client_size=sizeof(client_addr);
	
	client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
	
	if(client_sock<0)
	{
		printf("\nError while accepting");
		return(-1);
	}
	
	printf("\nClient connected at address:%s and port:%d",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port));
	
	
	while(1)
	{
		
		memset(client_message,'\0',sizeof(client_message));
		
		int num;
		
		if(recv(client_sock,&num,sizeof(num),0)<0)
		{
			printf("\nCouldnot recieve");
			return(-1);
		}
		
		printf("\nMessage recieved from client is:%d",num);
		
		
		
		int res=isPrime(num);
		
		
		if(send(client_sock,&res,sizeof(res),0)<0)
		{
			printf("\nCouldnot sent");
			return(-1);
		}
		printf("\nSend successfully");
		
		if(recv(client_sock,client_message,sizeof(client_message),0)<0)
		{
			printf("\nCouldnot recieve");
			return(-1);
		}
		
		if(strcmp(client_message,"no")==0)
			break;
		
		
	}
	
	printf("\n");
	
	
	//Close the sockets
	
	close(socket_desc);
	close(client_sock);
}


