#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[2000], client_message[2000];
	// Clean buffers:
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	// Create socket:
	socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if(socket_desc < 0)
	{
		printf("Unable to create socket\n");
		return -1;
	}
	printf("Socket created successfully\n");
	
	// Set port and IP the same as server-side:
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2002);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int server_size=sizeof(server_addr);
	
	while(1)
	{
		memset(&client_message,'\0',sizeof(client_message));
		memset(&server_message,'\0',sizeof(server_message));
		
		// Get input from the user:
		printf("Enter message:");
		fgets(client_message,sizeof(client_message),stdin);
		
		// Send the message to server:
		
		
		if(sendto(socket_desc, client_message, strlen(client_message), 0,(struct sockaddr*)&server_addr,server_size) < 0)
		{
			printf("Unable to send message\n");
			return -1;
		}
		
		if(strcmp(client_message,"exit\n")==0)
			break;
			
		// Receive the server's response:
		if(recvfrom(socket_desc, server_message, sizeof(server_message), 0,(struct sockaddr*)&server_addr,&server_size) < 0)
		{
			printf("Error while receiving server's msg\n");
			return -1;
		}
		
		printf("Server's response: %s\n",server_message);
		
		if(strcmp(server_message,"exit\n")==0)
			break;
	}
	
	// Close the socket:
	close(socket_desc);
	return(0);
}
