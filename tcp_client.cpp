// Server side C/C++ program to demonstrate Socket programming 
// Here's some include statements that might be helpful for you
#include <string> 
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) 
{ 
	// check to see if user input is valid
	char socket_read_buffer[1024];
	
	// TODO: Fill out the server ip and port
	std::string server_ip = "127.0.0.1";
	// std::string server_ip = "localhost";
	// std::string server_ip = "68.181.16.168";
	std::string server_port = "2000";

	int opt = 1;
	int client_fd = -1;
	int n = 0;

	// TODO: Create a TCP socket()
	// TCP socket with IPv4 performing default protocol
	client_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Enable reusing address and port
	if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		return -1;
	}

	// Check if the client socket was set up properly
	if(client_fd == -1){
		printf("Error- Socket setup failed\n");
		return -1;
	}
	
	// Helping you out by pepping the struct for connecting to the server
	struct addrinfo hints;
	struct addrinfo *server_addr;
	// sets all memory length in hints to 0
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	// takes human readable server_ip and Server_port and converts them into a C++ string
	// which it then server_addr
	getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints, &server_addr);

	// TODO: Connect() to the server (hint: you'll need to use server_addr)
	// next statement from linuxhowtos.org/data/6/client.c
	// Check if connection succeeds
	//if(connect(client_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
	if(connect(client_fd, server_addr->ai_addr, server_addr->ai_addrlen) < 0){	// using addrinfo struct (see info)
		printf("Error-Connection failed\n");
		return -1;
	}
	
	// TODO: Retreive user input
	// adapted from linuxhowtos.org/data/6/client.c
	printf("Please enter the message: ");
	bzero(socket_read_buffer,1024);
	fgets(socket_read_buffer, 1023, stdin);
	n = send(client_fd, socket_read_buffer, strlen(socket_read_buffer), 0);	// send() gives flags (write doesn't)
	if(n < 0){
		printf("Error- Socket write failed\n");
		return -1;
	}
	// TODO: Send() the user input to the server
	bzero(socket_read_buffer,1024);
	n = read(client_fd, socket_read_buffer, 1023);
	if(n < 0){
		printf("Error- Socket read failed\n");
		return -1;
	}
	printf("%s\n", socket_read_buffer);
	// TODO: Recieve any messages from the server and print it here. Don't forget to make sure the string is null terminated!
	// TODO: Close() the socket
	close(client_fd);
	return 0; 
} 
