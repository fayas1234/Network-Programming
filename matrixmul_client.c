//Program to implement	matrix multiplication using TCP client

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main()
{
	int socket_desc;
	
	char client_message[3];
	
	struct sockaddr_in server_addr,client_addr;
	
	memset(client_message,'\0',sizeof(client_message));
	
	
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(socket_desc<0)
	{
		printf("\nSocket not created");
		return(-1);
	
	}
	
	//Add addresses
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2005);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	printf("\nSocket created successfully");
	
	if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("\nCouldnot connect");
		return(-1);
	}
	
	printf("\nConnected successfully");
	
	while(1)
	{
		int size[2][2];
		
		while(1)
		{
			printf("\nEnter the number of rows and columns of matrix1 in order:");
			scanf("%d %d",&size[0][0],&size[0][1]);
			
			printf("\nEnter the number of rows and columns of matrix2 in order:");
			scanf("%d %d",&size[1][0],&size[1][1]);
			
			if(size[0][1]!=size[1][0])
			{
				printf("\nDimensions incompatable,so enter again");
			}
			
			else
			{
				break;
			}
		}
		
		int mat1[size[0][0]][size[0][1]],mat2[size[1][0]][size[1][1]];
		
		printf("\nEnter the matrix1:\n");
		for(int i=0;i<size[0][0];i++)
		{
			for(int j=0;j<size[0][1];j++)
			{
				scanf("%d",&mat1[i][j]);
			}
		}
		
		printf("\nEnter the matrix2:\n");
		for(int i=0;i<size[1][0];i++)
		{
			for(int j=0;j<size[1][1];j++)
			{
				scanf("%d",&mat2[i][j]);
			}
		}
		
		int prod[size[0][0]][size[1][1]];
			
	
	
		//Send dimensions
		if(send(socket_desc,size,sizeof(size),0)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSent successfully");
		
		//Send matrix1
		if(send(socket_desc,mat1,sizeof(mat1),0)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSent successfully");
		
		
		//Send matrix2
		if(send(socket_desc,mat2,sizeof(mat2),0)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSent successfully");
		
		
		if(recv(socket_desc,prod,sizeof(prod),0)<0)
		{
			printf("\nCouldnot recieve");
			return(-1);
		}
		
		
		printf("\nThe product matrix:\n");
		for(int i=0;i<size[0][0];i++)
		{
			for(int j=0;j<size[1][1];j++)
			{
				printf("%d\t",prod[i][j]);
			}
			printf("\n");
		}
		
		
		memset(client_message,'\0',sizeof(client_message));
		
		printf("\nDo you want to continue:");
		scanf("%s",client_message);
		
		if(send(socket_desc,client_message,sizeof(client_message),0)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSent successfully");
		
		if(strcmp(client_message,"no")==0)
			break;
			
		
	}
	printf("\n");
	
	//Closing the sockets
	close(socket_desc);
}
