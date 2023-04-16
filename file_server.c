//Program to implement server side TCP

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h> 

int cnt=0;

int main()
{
	int socket_desc,client_size,client_sock;
	FILE* f1;
	struct sockaddr_in client_addr,server_addr;
	char client_msg[4096],server_msg[4096];
	
	//Cleaning the buffers
	memset(&client_msg,'\0',sizeof(client_msg));
	memset(&server_msg,'\0',sizeof(server_msg));
	
	//creating the socket
	socket_desc=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	if(socket_desc<0)
	{
		printf("Socket creation unsuccessful\n");
		return(-1);
	}
	
	printf("Socket created successfully\n");
	pid_t child;
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2007);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//binding
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Couldn't bind to the port\n");
		return(-1);
	}
	
	printf("Done with binding\n");
	
	
	//listening for client
	
	if(listen(socket_desc,10)<0)
	{
		printf("Listening unsuccessful\n");
		return(-1);
	}
	
	printf("Listening for incoming connections\n");
	
	
	while (1) {
    client_size = sizeof(client_addr);

    //Accepting the connection
    client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);

    if (client_sock < 0) {
        printf("Cannot accept\n");
        return (-1);
    }

    printf("Client connected at ip:%s and port:%i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    printf("Client :%d connected\n\n", ++cnt);
    
    


    if ((child = fork()) == 0) {
        close(socket_desc);

            if (recv(client_sock, client_msg, sizeof(client_msg), 0) < 0) {
                printf("Couldn't receive the Client's message\n");
                return (-1);
            }
            printf("\nMessage from client %d:%s\n",cnt,client_msg);

            f1 = fopen(client_msg, "r");

            if (f1 == NULL) {
            
            	snprintf(server_msg,sizeof(server_msg),"pid:%d\n",getpid());
                strcat(server_msg, "not found");
                printf("%s asdas\n",server_msg);
                if (send(client_sock, server_msg, sizeof(server_msg), 0) < 0) {
                    printf("Couldn't Send Server's message\n");
                    return (-1);
                }
         
                exit(0);
            } else {
                printf("%d\n", getpid());
                snprintf(server_msg, sizeof(server_msg), "pid:%d\n", getpid());
                fgets(server_msg + strlen(server_msg), sizeof(server_msg) - strlen(server_msg), f1);
                
                printf("%s \n",server_msg);
                if (send(client_sock, server_msg, sizeof(server_msg), 0) < 0) {
                    printf("Couldn't Send Server's message\n");
                    return (-1);
                }
                fclose(f1);
                
              
                 exit(0);
            }
        close(client_sock);
    }
    
    
    
}
	close(client_sock);
	return(0);
}
	
	



