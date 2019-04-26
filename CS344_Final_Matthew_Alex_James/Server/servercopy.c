#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

int main(){
    int sockfd;
    int connfd;
    int len;

    struct sockaddr_in servaddr, client; /* Struct to store address of server and client */

    /* Create and verify our socket here */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); /* Creating the socket. AF_INET is the domain address of the socket, SOCK_STREAM shows the type of socket (here a TCP) */
    
    if(sockfd == -1){
        printf("Failed to create socket.");
        exit(0);
    } else {
        printf("Success!");
        bzero(&servaddr, sizeof(servaddr)); /* This specifies that we will set all values in a buffer to 0 */
    }

    /* Now let's assign our IP and Port */
    servaddr.sin_family = AF_INET; /* sin_family contains a code for the address family as demanded by our struct */
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); /* This contains our IP address for our host */
    servaddr.sin_port = htons(PORT); /* This contains our port number. We must convert it to network byte order using htons() */

    /* Now let us bind our socket to the IP and verify it */
    if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){
        printf("We failed to bind the socket.");
        exit(0);
    } else {
        printf("Bound!");
    }

    /* Time to start listening for our socket */
    if((listen(sockfd, 5)) != 0){
        printf("Listening failed.");
    } else {
        printf("Our server is now listening!");
        len = sizeof(client);
    }

    /* Let's accept our client's data packet and verify it */
    connfd = accept(sockfd, (SA*)&client, &len);
    if(connfd < 0){
        printf("Server failed to accept");
        exit(0);
    } else {
        printf("Accepted!");
    }
}