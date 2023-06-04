//Program to perform file copy using UDP server

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
	
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("\nCould not bind");
		return(-1);
	}
	printf("\nBinding successfull");
	
	
	
	int client_size=sizeof(client_addr);
	
	while(1)
	{	
		char f1[20],f2[20],result[100];
		memset(f1,'\0',sizeof(f1));
		memset(f2,'\0',sizeof(f2));
		memset(result,'\0',sizeof(result));
		
		if(recvfrom(socket_desc,f1,sizeof(f1),0,(struct sockaddr*)&client_addr,&client_size)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		
		FILE* fp1=fopen(f1,"r");
		
		if(recvfrom(socket_desc,f2,sizeof(f2),0,(struct sockaddr*)&client_addr,&client_size)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		
		FILE* fp2=fopen(f2,"w");
		
		if(fp1==NULL || fp2==NULL)
		{
			if(sendto(socket_desc,"File not found",sizeof("File not found"),0,(struct sockaddr*)&client_addr,sizeof(client_addr))<0)
			{
				printf("\nCouldnot send");
				return(-1);
			}	
		}
		
		else
		{
			char ch=fgetc(fp1);
			
			while(ch!=EOF)
			{
				fputc(ch,fp2);
				ch=getc(fp1);
			}
			
			if(sendto(socket_desc,"Done",sizeof("Done"),0,(struct sockaddr*)&client_addr,sizeof(client_addr))<0)
			{
				printf("\nCouldnot send");
				return(-1);
			}
			
			fclose(fp1);
			fclose(fp2);
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
