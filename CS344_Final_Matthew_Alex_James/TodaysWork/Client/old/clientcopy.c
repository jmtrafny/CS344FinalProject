#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

int main(){
    int sockfd;
    int connfd;
    
    struct sockaddr_in servaddr, client; /* Struct to store address of server and client */

    /* Let's create our socket and verify it's connection */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); /* Creating the socket. AF_INET is the domain address of the socket, SOCK_STREAM shows the type of socket (here a TCP) */

    if(sockfd == -1){
        printf("Failed to create socket.");
        exit(0);
    } else {
        printf("Success!");
        bzero(&servaddr, sizeof(servaddr)); /* This specifies that we will set all values in a buffer to 0 */
    }

    /* Here let's set up our IP and our Port */
    servaddr.sin_family = AF_INET; /* sin_family contains a code for the address family as demanded by our struct */
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); /* This gives our server the IP address */
    servaddr.sin_port = htons(PORT); /* This contains our port number. We must convert it to network byte order using htons() */

    /* Let's connect the client socket to the server socket */
    if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0){
        printf("Connection failed.");
        exit(0);
    } else {
        printf("Connected!");
    }
}