#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define RCVBUFSIZE 100   /* Size of receive buffer */
#define NAME_SIZE 21 /*Includes room for null */
#define DESC_SIZE 1001 //project description size
#define DATE_SIZE 9 //project date created and due size

#include "../HeaderFiles/menu.h"

typedef struct{
  unsigned int x;
  unsigned int y;
  unsigned char oper;
}TRANS_DATA_TYPE;

typedef struct{
  unsigned int x;
  unsigned int y;
}DATA_TYPE;

void DieWithError(char *errorMessage);  /* Error handling function */
void get(int, void *, unsigned int);
void put(int, void *, unsigned int);
void talkToServer(int);
unsigned int displayMenuAndSendSelection(int);
void sendProjectInformation(int);
void sendProjectID(int);
void sendProjectDescription(int);
void sendProjectCreationDate(int);
void sendProjectDueDate(int);
void sendProjectMemberNum(int);

int main(int argc, char *argv[]) {
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    char *echoString;                /* String to send to echo server */
    unsigned int echoStringLen;      /* Length of string to echo */
    int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv()
                                       and total bytes read */
    int answer;

    DATA_TYPE data;
    TRANS_DATA_TYPE incoming;
    memset(&incoming, 0, sizeof(TRANS_DATA_TYPE));

    if ((argc < 2) || (argc > 3))    /* Test for correct number of arguments */
    {
       fprintf(stderr, "Usage: %s <Server IP> [<Echo Port>]\n",
               argv[0]);
       exit(1);
    }

    servIP = argv[1];             /* First arg: server IP address (dotted quad) */

    if (argc == 3)
        echoServPort = atoi(argv[2]); /* Use given port, if any */
    else
        echoServPort = 7;  /* 7 is the well-known port for the echo service */

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    echoServAddr.sin_port        = htons(echoServPort); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

   // echoStringLen = strlen(echoString);          /* Determine input length */

    talkToServer(sock);

    close(sock);
    exit(0);
}

void talkToServer(int sock) {
    unsigned int selection = 0;
    unsigned char bye[5];

    while(1)
    {
        selection = displayMenuAndSendSelection(sock);
        printf("Client selected: %d\n", selection);
        switch(selection)
        {
            case 1:
                sendProjectInformation(sock);
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            }
        if(selection == 6) break;
    }
    selection = htonl(selection);
    put(sock, &selection, sizeof(unsigned int));
    get(sock, bye, 5);
    printf("%s\n", bye);
}

unsigned int displayMenuAndSendSelection(int sock) {
    MENU menuBuffer;     /* Buffer for echo string */
    unsigned int response = 0;
    unsigned int output;

    printf("Inside client display menu\n");
    get(sock, &menuBuffer, sizeof(struct menu));  //in this case server is also sending null
    printf("%s\n", menuBuffer.option1);
    printf("%s\n", menuBuffer.option2);
    printf("%s\n", menuBuffer.option3);
    printf("%s\n", menuBuffer.option4);
    printf("%s\n", menuBuffer.option5);
    printf("%s\n", menuBuffer.option6);
    scanf("%d", &response);
    output = htonl(response);
    put(sock, &output, sizeof(unsigned int));
    return response;
}

void sendProjectInformation(int sock) {
    sendProjectID(sock);
    sendProjectDescription(sock);
    sendProjectCreationDate(sock);
    sendProjectDueDate(sock);
    sendProjectMemberNum(sock);
}

void sendProjectID(int sock) {
    unsigned char msg[40];
    int number = 0;

    memset(msg, 0, sizeof(msg));
    get(sock, msg, sizeof(msg));
    printf("%s\n", msg);
    scanf("%d", &number);
    getchar(); //removing trailing whitespace -- scanf() can be very tricky!
    number = htonl(number);
    put(sock, &number, sizeof(int));
}

void sendProjectDescription(int sock) {
    unsigned char msg[40];
    unsigned char description[DESC_SIZE];

    memset(msg, 0, sizeof(msg));
    get(sock, msg, sizeof(msg));
    printf("%s\n", msg);
    memset(description, 0, DESC_SIZE);
    fgets(description, DESC_SIZE, stdin);
    put(sock, description, DESC_SIZE);
}

void sendProjectCreationDate(int sock) {
    unsigned char msg[40];
    unsigned char date[DATE_SIZE];

    memset(msg, 0, sizeof(msg));
    get(sock, msg, sizeof(msg));
    printf("%s\n", msg);
    memset(date, 0, DATE_SIZE);
    fgets(date, DATE_SIZE, stdin);
    put(sock, date, DATE_SIZE);
}

void sendProjectDueDate(int sock) {
    unsigned char msg[40];
    unsigned char date[DATE_SIZE];

    memset(msg, 0, sizeof(msg));
    get(sock, msg, sizeof(msg));
    printf("%s\n", msg);
    memset(date, 0, DATE_SIZE);
    fgets(date, DATE_SIZE, stdin);
    put(sock, date, DATE_SIZE);
}

void sendProjectMemberNum(int sock) {
    unsigned char msg[40];
    unsigned char memNum;

    memset(msg, 0, sizeof(msg));
    get(sock, msg, sizeof(msg));
    printf("%s\n", msg);
    scanf("%c", &memNum);
    put(sock, &memNum, sizeof(unsigned char));
}


