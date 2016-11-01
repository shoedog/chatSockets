/**
* Author: Wesley Jinks
* Date: 10/30/2016
* Last Mod: 10/31/2016
* File Name: client.c
*
* Overview: Chat client to recieve and send messages with chat-server over TCP
*
* Input: Usage: ./client <External Host> <Port>
*   handle: a 10 character string identifier
*   messages: a message to send to the server
*   disconnect: \quit
*
* Output: Prompts for input, messages from server, connection initialized and
*   connection terminated messages
*
* References:
*   Beej's Guide to Network Programming:
*       http://beej.us/guide/bgnet/
*
*   cplusplus: C Library Reference for Strings:
*       http://www.cplusplus.com/reference/cstring/
*
*   Pointer Related:
*       Ted Jensen Pointer Guide: http://pw1.netcom.com/~tjensen/ptr/pointers.htm
*       http://www.programiz.com/c-programming/c-structures-pointers
*       http://www.techcrashcourse.com/2015/08/c-programming-passing-pointer-function.html
*       http://stackoverflow.com/questions/346730/how-to-work-with-pointer-to-pointer-to-structure-in-c
*       http://stackoverflow.com/questions/4316314/pass-struct-by-reference-in-c
*       http://stackoverflow.com/questions/256148/passing-pointers-references-to-structs-into-functions
*
*   MakeFile Related:
*       http://www.cs.umd.edu/class/fall2002/cmsc214/Tutorial/makefile.html
*       http://www.cprogramming.com/tutorial/makefiles.html
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "utilsIO.h"

#define MAXDATASIZE 501
#define INIT_MSG  printf("\n\n\n\n\n\t***WELCOME TO CHAT***\n\n\n")


// Get pointer to ip4 or ip6 using sock_addr_in
void *get_in_addr(struct sockaddr *); 

// Sets addrinfo initializer, and calls getaddrinfo to fill pointer to addrinfo
int setStructs(char*[], struct addrinfo *, struct addrinfo **);

// Connect over socket to external address via TCP
int initiateContact(int *, struct addrinfo *);

// Send a message over connected socket
int sendMessage(int *, char *);

// Receive a message over connected socket
int receiveMessage(int *);

// Look for '\quit' command to terminate connection
int findQuit(char *);


int main(int argc, char*argv[]){

    int sockfd;                   // socket file descriptor
    struct addrinfo hints;        // address info initializer
    struct addrinfo *servinfo;    // pointer to getaddrinfo() results
    char clientHandle[11];        // 10 char Handle for client
    char message[501];            // 500 char message

    INIT_MSG;

    if(argc != 3 ) {
        fprintf(stderr, "usage: client hostname port\n");
        exit(1);
    }

    getHandle(clientHandle, 11);

    memset(&hints, 0, sizeof hints);        // make sure struct is empty
    setStructs(argv, &hints, &servinfo);    // set external address and socket

    initiateContact(&sockfd, servinfo);     // connect to server over socket
    sendMessage(&sockfd, clientHandle);     // send initial msg (Handle)

    // Loop to recieve and send messages while connected
    while(1){
        if ( receiveMessage(&sockfd) == 1 )
            break;

        messagePrompt(message);
        if ( sendMessage(&sockfd, message) == 1 )
            break;

        message[0] = '\0';
    }

    freeaddrinfo(servinfo);
    close(sockfd);

    return 0;
}

/******************************************************************************
*   Function: *get_in_addr
*
*   Description: Get pointer to ip4 or ip6 using sock_addr_in
*
*   Entry: Socket to reference
*
*   Exit: Socket with sin_addr or sin_addr6 set
*
*   Purpose: Determine if IP4 or IP6 and fill sin_addr appropriately
*
******************************************************************************/
void *get_in_addr(struct sockaddr *sa) {

    // Fill IP4 address
    if ( sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    // Fill IP6 address
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/******************************************************************************
*   Function: setStructs
*
*   Description: Sets addrinfo initializer, and calls getaddrinfo to fill
*       pointer to addrinfo for external connection
*
*   Entry: argv[]: array of arguments: [1]: IP Address, [2]: PORT
*          *hints: initial addrinfo options
*          **servinfo: addrinfo reference to initialize
*
*   Exit: 0 on success, with **servinfo addrinfo initialized
*         1 with error message on error
*
*   Purpose: Fill address info for external connection(server)
*
******************************************************************************/
int setStructs(char*argv[], struct addrinfo *hints, struct addrinfo **servinfo){
    int status;     // status of filling addrinfo with getaddrinfo

    //Set header ints
    hints->ai_family = AF_UNSPEC;      // allow IPv4 or IPv6
    hints->ai_socktype = SOCK_STREAM;  // TCP

    //Call get Address Info
    if ((status = getaddrinfo(argv[1], argv[2], hints, servinfo )) != 0 ) {
        fprintf( stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    return 0;
}

/******************************************************************************
*   Function: initiateContact
*
*   Description: Initializes socket and connects to external host
*
*   Entry: *sockfd: the socket file descriptor to initialize
*          *servinfo: the addrinfo for the host to initialize socket & connect
*
*   Exit: returns 0 on success with connection message
*         returns 2 on failure with error message
*
*   Purpose: Connect over socket to external address via TCP
*
******************************************************************************/
int initiateContact(int *sockfd, struct addrinfo *servinfo){
    struct addrinfo  *p;        // address info pointer to loop over servinfo
    char s[INET6_ADDRSTRLEN];   // address string length

    // Loop over addrinfo to fill socket file descriptor
    for ( p = servinfo; p != NULL; p = p -> ai_next ) {

        // Fill socket file descriptor: domain, type, protocol
        if ( ( *sockfd = socket(
            servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol) )
            == -1 ) {
                perror("client: socket");
                continue;
            }

        // connect with sockfd, server_address, server address length
        if ( connect( *sockfd, servinfo->ai_addr, servinfo->ai_addrlen ) == -1 ) {
            close(*sockfd);
            perror("client connect");
            continue;
        }

        break;
    }

    // Print error message on connect failure
    if ( p == NULL ) {
        fprintf(stderr, "client failed to connect \n");
        return 2;
    }

    // Convert IP address to string
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connecting to %s\n", s );

    return 0;
}

/******************************************************************************
*   Function: sendMessage
*
*   Description: Send a message over socket to host
*
*   Entry: *sockfd: initialized socket file descriptor connected to host
*          *msg: message to send
*
*   Exit: Return value if '\quit' was found in message:
*           1 to quit, 0 to maintain connection
*
*   Purpose: Send message over socket
*
******************************************************************************/
int sendMessage(int *sockfd, char *msg){
	int len;  // message length

	// set message length
    len = strlen(msg);

	// send message
	if( send(*sockfd, msg, len, 0) == -1 )
		perror("send");

	return findQuit(msg);
}

/******************************************************************************
*   Function: receiveMessage
*
*   Description: Receive message over socket
*
*   Entry: *sockfd: initialized socket file descriptor connected to host
*
*   Exit: Return value if '\quit' was found in message:
*           1 to quit, 0 to maintain connection
*
*   Purpose: Receive message over socket
*
******************************************************************************/
int receiveMessage(int *sockfd){
    int numbytes;           // bytes received
    char buf[MAXDATASIZE];  // max size to receive

    // Receive message
    if ( (numbytes = recv( *sockfd, buf, MAXDATASIZE-1, 0 ) ) == -1 ) {
        perror("recv");
        exit(1);
    }

    // Strip trailing newline
    buf[numbytes] = '\0';

    // look for '\quit' message to close connection
    if( findQuit(buf) != 0 ){
        return 1;
    }

    // Print Connection message
    printf("%s \n", buf);

    return 0;
}

/******************************************************************************
*   Function: findQuit
*
*   Description: Searches message string for '\quit' command to close connection
*
*   Entry: *message: a message to parse
*
*   Exit: returns 1 if '\quit' found to terminate connection
*         returns 0 if not found to keep connection open
*
*   Purpose: Find quit command to close connection
*
******************************************************************************/
int findQuit(char *message){
    char *quit;
    char remoteName[6];

    if((quit = strstr(message, "\\quit")) != NULL ) {
        strncpy( remoteName, message, 5 );
        printf("Connection to %s terminated.\n", remoteName );
        return 1;
    } else {
        return 0;
    }
}

