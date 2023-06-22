#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[4096], client_message[4096];
	// Clean buffers:
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	
	
	int size;
	printf("\nEnter the number of frames:");
	scanf("%d",&size);
	

	
	
	// Create socket:
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socket_desc < 0)
	{
		printf("Unable to create socket\n");
		return -1;
	}
	printf("Socket created successfully\n");
	
	// Set port and IP the same as server-side:
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2007);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	// Send connection request to server:
	if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Unable to connect\n");
		return -1;
	}
	printf("Connected with server successfully\n");
	
	snprintf(client_message,sizeof(client_message),"%d",size);
		
	// Send the message to server:
	if(send(socket_desc, client_message, strlen(client_message), 0) < 0)
	{
		printf("Unable to send message\n");
		return -1;
	}
	
	sleep(1);
	int i=0,count=0,ack=0,sent=0;
	
	while(i<4)
	{
		sent++;
		
		
		memset(server_message,'\0',sizeof(server_message));
		memset(client_message,'\0',sizeof(client_message));
		
		
		snprintf(client_message,sizeof(client_message),"%d",count);
		
		// Send the message to server:
		if(send(socket_desc, client_message, strlen(client_message), 0) < 0)
		{
			printf("Unable to send message\n");
			return -1;
		}
		
		if(sent==size*4)
			break;
		
		if(count==ack+size-1)
		{
			
			// Receive the server's response:
			if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0)
			{
				printf("Error while receiving server's msg\n");
				return -1;
			}
			printf("Server's response: %s\n",server_message);
			
			i++;
			
			if(atoi(server_message)!=count+1)
			{
			
				int neg=atoi(server_message);
				count=neg;
				
				ack=neg;
				
				continue;
			
			}
			else
			{
				ack=atoi(server_message);
			}
			
			
		}
		
		sleep(1);
		count++;
	}
	// Close the socket:
	close(socket_desc);
	return(0);
}
