//Program to implement TCP concurrent file server

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	int socket_desc,client_sock;
	
	char client_message[4096],server_message[4096];
	
	memset(server_message,'\0',sizeof(server_message));
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
	int count=0;
	
	printf("\nClient connected at address:%s and port:%d",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port));
	
	pid_t child;
	while(1)
	{
		int client_size=sizeof(client_addr);
		
		client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
		
		if(client_sock<0)
		{
			printf("\nError while accepting");
			return(-1);
		}
		
		printf("Client connected at ip:%s and port:%i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

   	 	printf("Client :%d connected\n\n", ++count);
		
			
		if((child=fork())==0)
		{
			close(socket_desc);
			
			
			
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));
			
			if(recv(client_sock,client_message,sizeof(client_message),0)<0)
			{
				printf("\nCouldnot recieve");
				return(-1);
			}
			
			printf("\nMessage recieved from client %d is:%s",count,client_message);
			
			FILE* f1=fopen(client_message,"r");
			
			pid_t pid=getpid();
			
			snprintf(server_message,sizeof(server_message),"pid:%d||",pid);
			
			if(f1==NULL)
			{
				strcat(server_message," file not found");
				if(send(client_sock,server_message,sizeof(server_message),0)<0)
				{
					printf("\nCouldnot sent");
					return(-1);
				}
				printf("\nSend successfully\n\n");
			}
			
			else
			{
				snprintf(server_message,sizeof(server_message),"pid:%d||",pid);
				
				while(fgets(server_message+strlen(server_message),sizeof(server_message)-strlen(server_message),f1));
				
				if(send(client_sock,server_message,sizeof(server_message),0)<0)
				{
					printf("\nCouldnot sent");
					return(-1);
				}
				printf("\nSend successfully\n\n");
				
				fclose(f1);
			
			}
			exit(0);
			
		}
	
	}
	printf("\n");
	
	
	//Close the sockets
	
	close(socket_desc);
	close(client_sock);
}
