/*
Authors: Dr. Bethelmy, Alex Hall, James Trafny, Matthieu Privat
Date: 27 April, 2019
File: clientWithMenu.c

This file prints a menu to the client regarding options they may choose for their project handling.
This can be either creating a project, saving a project, or anything else of the sort.
*/

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
#include "../HeaderFiles/linkedList.h"
#include "../HeaderFiles/projectStructure.h"

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

/*
Function: main()
------------------------------
This function creates our TCP connection with the server and calls the talkToServer() method.

sock: This is the socket descriptor
sockaddr_in echoServAddr: Echo server address
echoServPort: Echo server port
*servIP: This is a pointer to our Server IP address
*echoString: This is a pointer to our string to be sent to the echo server
echoStringLen: The length of the string sent to the echo server
byteRcvd: The bytes received in a single recv()
totalBytesRcvd: The total amount of bytes read

returns: none
*/

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

/*
Function: talkToServer()
------------------------------
This function allows the user to choose an option from the displayMenuAndSelection() method.

selection: An unsigned integer used for our switch statement to tell which option was picked.
bye: An unsigned char with space for 6 bytes.
*/

void talkToServer(int sock) {
    unsigned int selection = 0;
    unsigned char bye[5];
    unsigned int selectionb = 0;

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

                while(2) {
                    selectionb = displayMenuAndSendSelection(sock);

                    switch(selectionb)
                    {
                        case 1:
                            sendProjectID(sock);
                            break;
                        case 2:
                            sendProjectDescription(sock);
                            break;
                        case 3:
                            sendProjectCreationDate(sock);
                            break;
                        case 4:
                            sendProjectDueDate(sock);
                            break;
                        case 5:
                            sendProjectMemberNum(sock);
                            break;
                        }
                    if(selectionb == 6) break;
                }
                selectionb = htonl(selectionb);
                put(sock, &selectionb, sizeof(unsigned int));
                get(sock, bye, 5);
                printf("%s\n", bye);
                break;
            case 3:

                break;
            case 4:
                printf("Saving file to out.file\n");
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

/*
Function: displayMenuAndSelection()
-------------------------------------------
A method that displays the menu of options for the user when called.

menuBuffer: This is a buffer for an echo string
response: This is the unsigned integer corresponding to the option the user picked
output: An unsigned integer that converts reponse to network byte order

returns: response
*/

unsigned int displayMenuAndSendSelection(int sock) {
    MENU menuBuffer;     /* Buffer for echo string */
    unsigned int response = 0;
    unsigned int output;

    printf("Please select from the menu:\n");
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

/*
Function: sendProjectInformation()
----------------------------------------
A brief method that sends the information on a project to the client for them to view.

returns: void
*/

void sendProjectInformation(int sock) {
    sendProjectID(sock);
    sendProjectDescription(sock);
    sendProjectCreationDate(sock);
    sendProjectDueDate(sock);
    sendProjectMemberNum(sock);
}

/*
Function sendProjectID()
----------------------------------
A method that prompts the client to enter an ID number for the current project.

msg: An unsigned char that displays the prompt
number: The ID number that the client gives

returns: void
*/

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

/*
Function: sendProjectDescription()
------------------------------------
A method that sends a description of the project.

msg: An unsigned char that acts as our prompt
description: An unsigned char that stores the project description and prints it when
asked to.

returns: void
*/

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

/*
Function: sendProjectCreationDate()
--------------------------------------
A method that prints the date that the project was created.

msg: An unsigned char that acts as our prompt
date: An unsigned char that stores the creation date of the project

returns: void
*/

void sendProjectCreationDate(int sock) {
    unsigned char msg[40];
    unsigned char date[DATE_SIZE];

    memset(msg, 0, sizeof(msg));
    get(sock, msg, sizeof(msg));
    printf("%s\n", msg);
    memset(date, 0, DATE_SIZE);
    fgets(date, DATE_SIZE, stdin);
    getchar();
    put(sock, date, DATE_SIZE);
}

/*
Function: sendProjectDueDate()
--------------------------------------
A method that prints the date that the project is due.

msg: An unsigned char that acts as our prompt
date: An unsigned char that stores the due date of the project

returns: void
*/

void sendProjectDueDate(int sock) {
    unsigned char msg[40];
    unsigned char date[DATE_SIZE];

    memset(msg, 0, sizeof(msg));
    get(sock, msg, sizeof(msg));
    printf("%s\n", msg);
    memset(date, 0, DATE_SIZE);
    fgets(date, DATE_SIZE, stdin);
    getchar();
    put(sock, date, DATE_SIZE);
}

/*
Function: sendProjectMemberNum()
---------------------------------------
A method that send the number of members working on a given project.

msg: An unsigned char that acts as our prompt
memNum: An unsigned char that stores the number of members

returns: void
*/

void sendProjectMemberNum(int sock) {
    unsigned char msg[40];
    unsigned char memNum;

    memset(msg, 0, sizeof(msg));
    get(sock, msg, sizeof(msg));
    printf("%s\n", msg);
    scanf("%c", &memNum);
    put(sock, &memNum, sizeof(unsigned char));
}


