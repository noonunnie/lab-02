/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     * argc is an integer type parameter that is passed as an argument to the function when it is called
     * the parameter *argv[] is an array of pointers (C++ strings) that is passed as an argument to the function when it is called
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
     * following information found on chatGPT
     * a file descriptor is an address that represents any file on your computeer
     * a file descriptor table holds the file descriptors and some information about the files in a data structure so that the OS can track the files
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     * a struct is a datatype that can hold multiple types of corresponding variables in an organized tablelike format
     */
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
     * following information found on chatGPT
     * the three parameters for socket() are the...
     * 'domain': the address domain; AF_INET is for a IPv4
     * 'type': the type of socket; SOCK_STREAM is for TCP
     * 'protocol': 0 means use the default protocol
     * socket() returns an integer that identifies a socket, in this case it is stored in the integer sockfd 
     */
    
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
     * following information found on chatGPT
     * bind()'s parameters are...
     * 'sockfd': the output of socket()
     * 'addr': a pointer to a 'sockaddr' structure, which contains information about the address to bind to
     * 'addrlen': The length of the sockaddr structure in bytes
     * bind associates a socket with an (for us, IPv4) address
     
     * listen()'s parameters are...
     * 'sockfd': The socket descriptor returned by the socket() function, which should be bound to a specific address with the bind() function before calling listen()
     * 'backlog': Defines the maximum number of ions that can be waiting while the process is handling a particular connection
     * listen is used to mark a socket as a passive socket, meaning it can accept incoming connections
     */
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1) {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
        * we use while(1) so that the code wil continue to run until there is an error. If there are multiple connections only one can be handled at a time
        which will cause backlogging
        */
        
	char buffer[256];
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
	/* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
	 * cite: https://www.geeksforgeeks.org/fork-system-call/
         * fork will run multiple simultaneous connections in parallel so that one connection is not prohibiting another from going through
         */
        
	if (newsockfd < 0) 
             error("ERROR on accept");
	bzero(buffer,256);
        
	n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        //printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",18);
        if (n < 0) 
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}
  
/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
 * Answer from chatGPT
 * A system call is a request made by a program to the operating system (OS) or kernel for a specific service or action.System calls are typically made
in the form of a function call, but are made to the kernel rather than to a library or other user-space program. They are used to perform low-level 
operations that are not possible with regular library calls, and are specific to a particular operating system and architecture.
 */
