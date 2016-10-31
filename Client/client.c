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

// server on flip3.engr.oregonstate.edu
// server ipaddr: 128.193.36.41

#define MAXDATASIZE 100
#define CLEAR  printf("\n\n\n\n\n\t***WELCOME TO CHAT***\n\n\n")

//Get ip4 or ip6
void *get_in_addr(struct sockaddr *); 

int setStructs(char*[], struct addrinfo *, struct addrinfo **);

int initiateContact(int *, struct addrinfo *);

int sendMessage(int *, char *);

int recieveMessage(int *);

int findQuit(char *);


int main(int argc, char*argv[]){

  int sockfd;
  struct addrinfo hints, *servinfo;
  char clientHandle[11];
  char message[501];

  CLEAR;

  if(argc != 3 ) {
    fprintf(stderr, "usage: client hostname port\n");
    exit(1);
  }
  

  getHandle(clientHandle, 11);

  memset(&hints, 0, sizeof hints);  // make sure struct is empty
  setStructs(argv, &hints, &servinfo);
  
  initiateContact(&sockfd, servinfo);
  sendMessage(&sockfd, clientHandle);

  while(1){
    if ( recieveMessage(&sockfd) == 1 )
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

//Get ip4 or ip6
void *get_in_addr(struct sockaddr *sa) {
  if ( sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int setStructs(char*argv[], struct addrinfo *hints, struct addrinfo **servinfo){
  int status;

  //Set header ints
  hints->ai_family = AF_UNSPEC;      // allow IPv4 or IPv6
  hints->ai_socktype = SOCK_STREAM;  // TCP

  //Call get Address Info
  if ((status = getaddrinfo(argv[1], argv[2], hints, servinfo )) != 0 ) {
 // if ((status = getaddrinfo(argv[1], argv[2], &hints, &servinfo )) != 0 ) {
    fprintf( stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    return 1;
  }
  return 0;
}

int initiateContact(int *sockfd, struct addrinfo *servinfo){
  struct addrinfo  *p;
  char s[INET6_ADDRSTRLEN];

  for ( p = servinfo; p != NULL; p = p -> ai_next ) {
    //get pointer to address
	//Make socket file descriptor: domain, type, protocol
	if ((*sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, 
	  servinfo->ai_protocol)) == -1 ) {
       perror("client: socket");
       continue;
     }
  
    //connect with sockfd, server_address, server address length
    if (connect(*sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1 ) {
      close(*sockfd);
      perror("client connect");
      continue;
    }

    break;
  }

  if ( p == NULL ) {
    fprintf(stderr, "client failed to connect \n");
    return 2;
  }
  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
  printf("client: connecting to %s\n", s );

  return 0;
}

int sendMessage(int *sockfd, char *msg){
	int len;
	
    len = strlen(msg);
	
	if( send(*sockfd, msg, len, 0) == -1 )
		perror("send");

	return findQuit(msg);
}

int recieveMessage(int *sockfd){
  int numbytes;
  char buf[MAXDATASIZE];
 
  if ((numbytes = recv(*sockfd, buf, MAXDATASIZE-1, 0 )) == -1 ) {
    perror("recv");
    exit(1);
  }

  buf[numbytes] = '\0';

  if( findQuit(buf) != 0 ){
    return 1;
  }
  
  //Connection message
  printf("%s \n", buf);

  return findQuit(buf);
}

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

