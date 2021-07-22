We provide a makefile to easily execute the code correctly
Command:	make s  compile server code and run.
		make c  compile client code and run.

When the server is on, it will keep write log on the terminal,
include new client connected (created a new thread to
handle the client message sending) and message send to clients.
Type in exit can shut down the server.
	
When a client is created, it will automatically try to connect
to the server if there exists one. If connected successfully,
system will ask user to type in a name to recognize in chatting.
After enter the chat room, the user can type in every message freely.
But the system distinguishes messages by the space, thus on sentence
will be separated to words and show on the terminal.
If the user wishes to leave the chatroom, just type in command bye.

Part B: Result
 
Figure 7. Server running screenshot

 
Figure 8. Three users chatting screenshot
