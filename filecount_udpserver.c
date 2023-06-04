//Program to perform the counting of lines and words using UDP server

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
		char fname[20],result[100];
		memset(fname,'\0',sizeof(fname));
		memset(result,'\0',sizeof(result));
		
		if(recvfrom(socket_desc,fname,sizeof(fname),0,(struct sockaddr*)&client_addr,&client_size)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		
		FILE* f1=fopen(fname,"r");
		
		if(f1==NULL)
		{
			if(sendto(socket_desc,"File not found",sizeof("File not found"),0,(struct sockaddr*)&client_addr,sizeof(client_addr))<0)
			{
				printf("\nCouldnot send");
				return(-1);
			}	
		}
		
		else
		{
			int lines=1,words=0;
			
			char ch=fgetc(f1);
			
			while(ch!=EOF)
			{
				if(ch==' ')
					words++;
				else if(ch=='\n')
				{
					words++;
					lines++;
				}
				ch=fgetc(f1);
			}
			
			snprintf(result,sizeof(result),"Line cout:%d||Word count:%d",lines,words);
			if(sendto(socket_desc,result,sizeof(result),0,(struct sockaddr*)&client_addr,sizeof(client_addr))<0)
			{
				printf("\nCouldnot send");
				return(-1);
			}	
			fclose(f1);
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
