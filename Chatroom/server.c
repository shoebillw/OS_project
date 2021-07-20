#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
 
int sockfd;									// Server socket
int fds[20];									// Socketfd of clients,at most 10 (fds[0]~fds[9])
int size =20;									// Max client number set to 10 (allow at most 10 users)
char* IP = "127.0.0.1";							// Connection IP number (return to this computer)
short PORT = 10222;								// Connection port
typedef struct sockaddr SA;							// Structure typd define, easy for coding
 
void init()									//Initialization code section of the server
{
	sockfd = socket(PF_INET, SOCK_STREAM, 0);				// Create the socket (use stream type; TCP type; no special protocol)
	if (sockfd == -1)							// Socket create failed
	{
		perror("Socket creation failed");				// Print out error message
		exit(-1);							// Exit the code and return nonzero number
	}
	
	struct sockaddr_in addr;						// Construct a socket address struct
	addr.sin_family = PF_INET;						// We use TCP, af variable = PF_INET
	addr.sin_port = htons(PORT);						// Function for changing host to network type
	addr.sin_addr.s_addr = inet_addr(IP);					// Transfer decimal address to binary address
	if (bind(sockfd, (SA*)&addr, sizeof(addr)) == -1)			// Binding function, check if binding success
	{									// Variable: socket name; socket address; length of address
		perror("Bnding failed");					// Print out error message
		exit(-1);							// Exit the code and return nonzero number
	}
	if (listen(sockfd, 20) == -1)						// Set the port to listening
	{
		perror("Listen deamon setting failed");			// Failed, print out error message
		exit(-1);							// Exit the code and return nonzero number
	}
}
 
void SendMsgToAll(char* msg)							// Send message to all users in the chat room log
{
	int i;
	for (i = 0; i < size; i++)						// To all users
	{
		if (fds[i] != 0)						// ENable fds number (users available number)
		{
			send(fds[i], msg, strlen(msg), 0);			// Send message in buffer to all users
			printf("Message sent to: %d\n",fds[i]);		// Print log			
		}
	}
}
 
void* service_thread(void* p)							// Create new thread for new client
{
	int fd = *(int*)p;							// Create a new thread id number
	printf("(Pthread id = %d)\n",fd);					// Print out log
	
	while(1)								// Thread running
	{
		char buf[100] = {};						// Chat message buffer
		if (recv(fd, buf, sizeof(buf), 0) <= 0)			// Recieve leaving message from client number fd
		{
			int i;
			for (i = 0; i < size; i++)				// Set the fds number to 0 (return the resource)
			{
				if (fd == fds[i])				// Find the fd number in vector fds
				{
					fds[i] = 0;				// Return the thread resuorce
					break;					// Break the for loop
				}
			}
			printf("User：fd = %d leaves the chat room\n",fd);	// Broadcast the leaving message to all users
			pthread_exit((void*)i);				// Exit the thread
		}		
		SendMsgToAll(buf);						// Send the message to all the users in the chat room and write log
	}
}
 
void* service(void* p)								// Service section, main section
{
	printf("Server on\n");							// Print out status when successfully connect the port
	while(1)
	{
		struct sockaddr_in fromaddr;					// Socket address datatype of port address
		socklen_t len = sizeof(fromaddr);				// Length of the address
		int fd = accept(sockfd, (SA*)&fromaddr, &len);		// Accept new connection from client
		if (fd == -1)
		{
			printf("Can't connect to client..\n");		// Error from connecting to client
			continue;						// Try again
		}
		
		int i = 0;
		for (i = 0; i < size; i++)
		{
			if (fds[i] == 0)
			{
				fds[i] = fd;					// Record the socket number of the client
				printf("fd = %d, ",fd);			// Print the fd number of client
				pthread_t tid;					// Create new thread to service the client
				pthread_create(&tid, 0, service_thread, &fd);
				break;
			}
			if (size == i)						// The chat room is now full
			{
				char* str = "The room is full!";		// Full message
				send(fd,str,strlen(str),0); 			// Send message to the new client
				close(fd);					// Stop servicing the new client
			}
		}
	}
}

void detect()									// Erads the terminal input (for shut down)
{
	pthread_t id;								// New thread for servicing
	void* service(void*);							// New service job
	pthread_create(&id, 0, service, 0);					// Add the recieve job to the thread
	while (1)
	{
		char buf[100] = {};
		scanf("%s",buf);
		if (strcmp(buf, "exit") == 0)					// User type in leaving keyword (exit)
		{
			printf("Server shut down\n"); 			// Print out leaving message
			break;							// Stop service
		}
	}
	close(sockfd);
}
 
int main()									// Main server.c code section
{
	init();								// Initialize server
	detect();								// Provide service after initialize successfully
	return(0);
}

