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



# Result:

![image](https://user-images.githubusercontent.com/80030514/126640888-636d63ec-da1f-4812-8245-eb8d83ef07a2.png)

Figure 7. Server running screenshot

![image](https://user-images.githubusercontent.com/80030514/126641614-006401a4-7571-41e2-b3d2-700d236c1ceb.png)
 
Figure 8. Three users chatting screenshot


# Explanation of code:
>Connection:

We create sockets to link server and clients. IP number is set to 127.0.0.1 to connect back to our computer, port number is set to 10222 a random number larger than 1024.
	
>Send and receive:

In both server and client, we create threads to send and receive messages.
On server side, server will receive message from every client, and broadcast
(send) to all the clients (include the message sender).
On client side, when user types message, client will send a message to the server. When the client receives the broadcast from server, it will show up on the screen.

# Flow chart:

![image](https://user-images.githubusercontent.com/80030514/126641188-68a2ebce-d112-4eaf-8e7e-8f7a10f21dc7.png)

# Structure chart: 

![image](https://user-images.githubusercontent.com/80030514/126641479-f8c56f7d-cae0-494d-9823-e4e023df8c89.png)



