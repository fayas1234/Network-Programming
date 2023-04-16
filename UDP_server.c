//Program to implement server side TCP
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>


int main()
{
	int socket_desc,client_size;
	
	struct sockaddr_in client_addr,server_addr;
	char client_msg[2000],server_msg[2000];
	
	client_size=sizeof(client_addr);
	
	//Cleaning the buffers
	memset(&client_msg,'\0',sizeof(client_msg));
	memset(&server_msg,'\0',sizeof(server_msg));
	
	//creating the socket
	socket_desc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	if(socket_desc<0)
	{
		return(-1);
	}
	
	printf("Socket created successfully\n");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2002);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//binding
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Couldn't bind to the port\n");
		return(-1);
	}
	
	printf("Done with binding\n");
	
	
	//Recieve clients message
	while(1)
	{
		memset(&client_msg,'\0',sizeof(client_msg));
		memset(&server_msg,'\0',sizeof(server_msg));
	
		if(recvfrom(socket_desc,client_msg,sizeof(client_msg),0,(struct sockaddr*)&client_addr,&client_size)<0)
		{
			printf("Couldn't recieve the Clients message\n");
			return(-1);
		}
		
		printf("Message recieved from the client is:%s\n",client_msg);
		
		if(strcmp(client_msg,"exit\n")==0)
			break;
			
		//Sending the message to client
		
		printf("Enter the message to be sent to the client:");
		fgets(server_msg,sizeof(server_msg),stdin);
		
		if(sendto(socket_desc,server_msg,sizeof(server_msg),0,(struct sockaddr*)&client_addr,client_size)<0)
		{
			printf("Couldn't Send Servers message\n");
			return(-1);
		}
		
		if(strcmp(server_msg,"exit\n")==0)
			break;
	}
	
	//Closing the socket

	close(socket_desc);
	return(0);
}
	
	



