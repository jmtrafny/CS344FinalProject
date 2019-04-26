#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <stdlib.h>
#include <string.h>
#include "../HeaderFiles/menu.h"
#include "../HeaderFiles/linkedList.h"
#include "../HeaderFiles/projectStructure.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */
#define NAME_SIZE 21 /*Includes room for null */



void DieWithError(char *errorMessage);  /* Error handling function */
void get(int, void *, unsigned int);
void put(int, void *, unsigned int);
unsigned int sendMenuAndWaitForResponse(int);
void createProject(int sock, PROJECT_STRUCT * project);

void HandleTCPClient(int clntSocket)
{
    int recvMsgSize;                    /* Size of received message */
    unsigned int response = 0;
    unsigned char name[NAME_SIZE]; //max length 20
    int number = 0;
    PROJECT_STRUCT * project = (PROJECT_STRUCT *) calloc (1, sizeof(PROJECT_STRUCT));
    unsigned char errorMsg[] = "Invalid Choice";
    unsigned char bye[] = "Bye!";

    response = sendMenuAndWaitForResponse(clntSocket);
    while(response != 6)
    {
        switch(response)
        {
            case 1: printf("Client created a project.\n");
                    createProject(clntSocket, project);
                    break;
            case 2: printf("Client is editing a project.\n");
                    break;
            case 3: printf("Client is deleting a project.\n");
                    break;
            case 4: printf("Client is saving a project.\n");
                    break;
            case 5: printf("Client is displaying a project.\n");
                    break;
            default: printf("Client selected junk.\n"); put(clntSocket, errorMsg, sizeof(errorMsg)); break;
        }
        response = sendMenuAndWaitForResponse(clntSocket);
    }//end while

    put(clntSocket, bye, sizeof(bye));
    close(clntSocket);    /* Close client socket */
    printf("Connection with client %d closed.\n", clntSocket);
}

unsigned int sendMenuAndWaitForResponse(int clntSocket) {
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
