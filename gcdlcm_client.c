//Progran to compute the gcd and lcm using UDP client

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
		int a,b,gcd,lcm;
		
		printf("\nEnter the two numbers:");
		scanf("%d %d",&a,&b);
		
		
		if(sendto(socket_desc,&a,sizeof(a),0,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSend successfully");
		
		if(sendto(socket_desc,&b,sizeof(b),0,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSend successfully");
		
		if(recvfrom(socket_desc,&gcd,sizeof(gcd),0,(struct sockaddr*)&server_addr,&server_size)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nGcd is:%d",gcd);
		
		if(recvfrom(socket_desc,&lcm,sizeof(lcm),0,(struct sockaddr*)&server_addr,&server_size)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nlcm is:%d",lcm);
		
		memset(client_message,'\0',sizeof(client_message));
		
		printf("\nDo you want to continue:");
		scanf("%s",client_message);
		
		if(sendto(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSend successfully");
		
		
		if(strcmp(client_message,"no")==0)
			break;
	}
	
	//close the sockets
	close(socket_desc);
		
}
		
		
		
		
		
		
