//Program to implement matrix multiplication using TCP server

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


		
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
		
		int size[2][2];
		
		if(recv(client_sock,size,sizeof(size),0)<0)
		{
			printf("\nCouldnot recieve");
			return(-1);
		}
		
		int mat1[size[0][0]][size[0][1]],mat2[size[1][0]][size[1][1]];
		
		if(recv(client_sock,mat1,sizeof(mat1),0)<0)
		{
			printf("\nCouldnot recieve");
			return(-1);
		}
		
		if(recv(client_sock,mat2,sizeof(mat2),0)<0)
		{
			printf("\nCouldnot recieve");
			return(-1);
		}
		
		int prod[size[0][0]][size[1][1]];
		
		for(int i=0;i<size[0][0];i++)
		{
			
			for(int j=0;j<size[1][1];j++)
			{
				int sum=0;
				for(int k=0;k<size[0][1];k++)
				{
					sum+=mat1[i][k]*mat2[k][j];
				}
				prod[i][j]=sum;
			}
		}
		
		
		if(send(client_sock,prod,sizeof(prod),0)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		
		
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


