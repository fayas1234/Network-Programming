//Progran to appending in a file using UDP client

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

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
	
	int server_size=sizeof(server_addr);
	
	while(1)
	{	
		char f1[20],f2[20];
		memset(f1,'\0',sizeof(f1));
		memset(f2,'\0',sizeof(f2));
		
		printf("\nEnter the file name 1 with extension:");
		scanf("%s",f1);
		
		if(sendto(socket_desc,f1,sizeof(f1),0,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSend successfully");
		
		
		printf("\nEnter the file name 2 with extension:");
		scanf("%s",f2);
		
		if(sendto(socket_desc,f2,sizeof(f2),0,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSend successfully");
		
		
		char result[100];
		
		if(recvfrom(socket_desc,result,sizeof(result),0,(struct sockaddr*)&server_addr,&server_size)<0)
		{
			printf("\nCouldnot recieve");
			return(-1);
		}
		printf("\nMessage from the server is:%s",result);


		printf("\nDo you want to continue:");
		scanf("%s",client_message);
		
		if(sendto(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSend successfully\n");
		
		
		if(strcmp(client_message,"no")==0)
			break;
	}
	
	//close the sockets
	close(socket_desc);
		
}
		
		
		
		
		
		
