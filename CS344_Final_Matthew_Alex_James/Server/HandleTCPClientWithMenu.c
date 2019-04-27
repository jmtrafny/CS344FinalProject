/*
    Author:  Alex Hall
             Matthieu Privat
             James Trafny
    Date: 4/27/2019
    Program: HandleTCPClientWithMenu.c

    Description:

        This file is called after a connection has been 
        made to the client.  The program flow here goes: 
        send menu, wait for response, trigger fn based 
        on respone, send new menu, repeat
*/

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
void append(LINKED_LIST * listPtr, void * data);
//PROJECT_STRUCT * createProject(int sock);

/*
 * Function:  HandleTCPClient 
 * --------------------
 * Takes in a user socket and sends it a menu, after
 * sending the menu it waits for a response and triggers
 * a function based on the response.
 *
 *  clntSock: client socket
 *
 *  returns: void
 */
void HandleTCPClient(int clntSocket)
{
    int recvMsgSize;                    /* Size of received message */
    unsigned int response = 0;
    unsigned char name[NAME_SIZE]; //max length 20
    int number = 0;
    LINKED_LIST * project_list = (LINKED_LIST *) calloc(1, sizeof(LINKED_LIST));
    unsigned char errorMsg[] = "Invalid Choice";
    unsigned char bye[] = "Bye!";

    response = sendMenuAndWaitForResponse(clntSocket);
    while(response != 6)
    {
        switch(response)
        {
            case 1: 
            	printf("Client created a project.\n");
            	PROJECT_STRUCT * project = (PROJECT_STRUCT *) calloc (1, sizeof(PROJECT_STRUCT));
                project = createProject(clntSocket);
                append(project_list, project);
                printf("Project List size: %d\n", project_list->size);
                //printProject(project);
                break;
            case 2: 
            	printf("Client is editing a project.\n");
                break;
            case 3: 
            	printf("Client is deleting a project.\n");
                break;
            case 4: 
            	printf("Client is saving a project.\n");
                FILE * fp;
                sendToFile(project_list, fp);
                break;
            case 5: 
            	printf("Client is displaying a project.\n");
                break;
            default: 
            	printf("Client selected junk.\n"); 
            	put(clntSocket, errorMsg, sizeof(errorMsg)); 
            	break;
        }
        response = sendMenuAndWaitForResponse(clntSocket);
    }//end while

    put(clntSocket, bye, sizeof(bye));
    close(clntSocket);    /* Close client socket */
    printf("Connection with client %d closed.\n", clntSocket);
}

/*
 * Function:  sendMenuAndWaitForResponse 
 * --------------------
 * Takes in a user socket and sends it a menu
 *
 *  clntSock: client socket
 *
 *  returns: integer choice from user
 */
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
