#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
 
int sockfd;									// Client soclet number
char* IP = "127.0.0.1";							// Server IP number
short PORT = 10222;								// Server port number
typedef struct sockaddr SA;
char name[30];									// String of the client name
 
void init()									// Initialization sevtion of client code
{
	sockfd = socket(PF_INET, SOCK_STREAM, 0);				// Create the socket
	struct sockaddr_in addr;						// Construct a socket address struct
	addr.sin_family = PF_INET;						// We use TCP, af variable = PF_INET
	addr.sin_port = htons(PORT);						// Function for changing host to network type
	addr.sin_addr.s_addr = inet_addr(IP);					// Transfer decimal address to binary address
	if (connect(sockfd, (SA*)&addr, sizeof(addr)) == -1)			// Try connection
	{
		perror("Can't conect to the server\n");			// Connection fail
		exit(-1);							// Exit the code and return nonzero number
	}
	printf("Connect success!\n");						// Connection success
}
 
void start()									// Service of client, main part
{
	pthread_t id;								// New thread for recieving message
	void* recv_thread(void*);						// New recieve job
	pthread_create(&id, 0, recv_thread, 0);				// Add the recieve job to the thread
	char buf2[100] = {};							// Maeeage buffer
	sprintf(buf2, "User: %s enters the chat room", name);		// Show enter message
	send(sockfd, buf2, strlen(buf2), 0);					// Send the same message to every other user in the room

	while(1)
	{
		char buf[100] = {};						// Message buffer
		scanf("%s", buf);						// User type in message
		char msg[133] = {};						// Send message buffer
		sprintf(msg, "%s: %s\n", name, buf);				// Message that will show on everyone screen
		send(sockfd, msg,strlen(msg), 0);				// Send to server
		if (strcmp(buf, "bye") == 0)					// User type in leaving keyword (bye)
		{
			memset(buf2, 0, sizeof(buf2));			// Set message to leave message
			sprintf(buf2, "User: %s leaves the room\n", name);	// Print out leaving message
			send(sockfd, buf2, strlen(buf2), 0);			// Send to all other user in the room
			break;							// Stop service
		}
	}
	close(sockfd);								// Close the socket
}
 
void* recv_thread(void* p)							// Message reciving method
{
	while(1)								// Keep reciving
	{
		char buf[100] = {};						// Message buffer
		if (recv(sockfd, buf, sizeof(buf), 0) <= 0)			// If didn't recieve any message (buffer is empty)
		{
			return (0);						// Skip
		}
		printf("%s\n", buf);						// Else, print the message
	}
}
 
int main()									// Main client.c code section
{
	init();								// Initialize client
	printf("Please enter your name： ");					// Ask the name of user
	scanf("%s", name);							// Read the type in of the user
	start();								// Start the service of client
	return 0;								// Stop service when user leaves
}

