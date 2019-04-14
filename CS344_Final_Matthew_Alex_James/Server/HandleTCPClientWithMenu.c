#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <stdlib.h>
#include <string.h>
#include "../HeaderFiles/menu.h"
#include "../HeaderFiles/projectStructure.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */
#define NAME_SIZE 21 /*Includes room for null */
#define DESC_SIZE 1001 //project description size
#define DATE_SIZE 9 //project date created and due size


void DieWithError(char *errorMessage);  /* Error handling function */
void get(int, void *, unsigned int);
void put(int, void *, unsigned int);
unsigned int sendMenuAndWaitForResponse(int);
void askForName(int sock, char *, unsigned int);
void doSomethingWithName(char *);
void askForNumber(int sock, int *, unsigned int);
void doSomethingWithNumber(int);

void HandleTCPClient(int clntSocket)
{
    int recvMsgSize;                    /* Size of received message */
    unsigned int response = 0;
    unsigned char name[NAME_SIZE]; //max length 20
    int number = 0;
    unsigned char errorMsg[] = "Invalid Choice";
    unsigned char bye[] = "Bye!";

    response = sendMenuAndWaitForResponse(clntSocket);
    while(response != 3)
    {
        switch(response)
        {
            case 1: printf("Client selected 1.\n");
                    askForName(clntSocket, name, NAME_SIZE);
                    doSomethingWithName(name);
                    break;
            case 2: printf("Client selected 2.\n");
                    askForNumber(clntSocket, &number, sizeof(int));
                    doSomethingWithNumber(number);
                    break;
            default: printf("Client selected junk.\n"); put(clntSocket, errorMsg, sizeof(errorMsg)); break;
        }
        response = sendMenuAndWaitForResponse(clntSocket);
    }//end while

    put(clntSocket, bye, sizeof(bye));
    close(clntSocket);    /* Close client socket */
    printf("Connection with client %d closed.\n", clntSocket);
}

unsigned int sendMenuAndWaitForResponse(int clntSocket)
{
    MENU mainMenu;
    unsigned int response = 0;
    memset(&mainMenu, 0, sizeof(MENU));   /* Zero out structure */
    strcpy(mainMenu.option1,"1) Create project\n");
    strcpy(mainMenu.option2, "2) Edit project\n");
    strcpy(mainMenu.option3, "3) Delete project\n");
    strcpy(mainMenu.option4, "4) Save project\n");
    strcpy(mainMenu.option5, "5) Display project\n");
    strcpy(mainMenu.option6, "6) Exit program\n");
    printf("Sending menu\n");
    put(clntSocket, &mainMenu, sizeof(MENU));
    get(clntSocket, &response, sizeof(unsigned int));
    return ntohl(response);
}

//"ask" portion of create project
void createProject(int sock, PROJECT_STRUCT * project, unsigned int iSize) {
    askForProjectID(sock, project->proj_id, iSize);




    doSomethingWithNumber()
}



void askForProjectID(int sock, int * numPtr, unsigned int size)
{
    unsigned char msg[40];
    int numIn = 0;

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter project number ID:\n");
    put(sock, msg, sizeof(msg));
    get(sock, &numIn, sizeof(int));
    *numPtr = ntohl(numIn);
}

void doSomethingWithNumber(int number)
{
    printf("Received number from the client: %d\n", number);
}

void askForProjectDescription(int sock, char * stringPtr,  size)
{
    unsigned char msg[21];
    int numIn = 0;

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter number:\n");
    put(sock, msg, sizeof(msg));
    get(sock, &numIn, sizeof(int));
    *numPtr = ntohl(numIn);
}

void doSomethingWithName(char * name)
{
    printf("Received name from the client: %s\n", name);
}
