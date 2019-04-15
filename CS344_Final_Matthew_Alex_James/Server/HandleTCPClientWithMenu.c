#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <stdlib.h>
#include <string.h>
//#include "../HeaderFiles/menu.h"
//#include "../HeaderFiles/linkedList.h"
//#include "../HeaderFiles/projectStructure.h"

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


typedef struct project_struct{
	int proj_id;
	char proj_desc[1000];
	char proj_date_created[9];
	char proj_date_due[9];
	unsigned char proj_num_members;
	//LINKED_LIST proj_member_list;
} PROJECT_STRUCT;

typedef struct menu{
	unsigned char option1[40];
	unsigned char option2[40];
	unsigned char option3[40];
	unsigned char option4[40];
	unsigned char option5[40];
	unsigned char option6[40];
} MENU;

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

//"ask" portion of create project
void createProject(int sock, PROJECT_STRUCT * project) {
    askForProjectID(sock, project->proj_id, sizeof(project->proj_id));
    askForProjectDescription(sock, project->proj_desc, DESC_SIZE);
    askForProjectDateCreated(sock, project->proj_date_created, DATE_SIZE);
    askForProjectDateDue(sock, project->proj_date_due, DATE_SIZE);
    askForMemberNum(sock, project->proj_num_members, sizeof(project->proj_num_members));
    printf("This ran successfully.\n");
}



void askForProjectID(int sock, int * numPtr, unsigned int size) {
    unsigned char msg[40];
    int numIn = 0;

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter project number ID:\n");
    put(sock, msg, sizeof(msg));
    printf("Before get() in askForProjectID().\n");
    get(sock, &numIn, size);
    printf("After get() in askForProjectID().\n");
    *numPtr = ntohl(numIn);
}

void askForProjectDescription(int sock, char * stringPtr, unsigned int size) {
    unsigned char msg[40];

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter project description:\n");
    put(sock, msg, sizeof(msg));
    memset(stringPtr, 0, DESC_SIZE);
    printf("Before get() in askForProjectDescription().\n");
    get(sock, stringPtr, DESC_SIZE);
    printf("After get() in askForProjectDescription().\n");
}

void askForProjectDateCreated(int sock, char * stringPtr, unsigned int size) {
    unsigned char msg[40];

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter project creation date:\n");
    put(sock, msg, sizeof(msg));
    memset(stringPtr, 0, DATE_SIZE);
    get(sock, stringPtr, DATE_SIZE);
}

void askForProjectDateDue(int sock, char * stringPtr, unsigned int size) {
    unsigned char msg[40];

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter project due date:\n");
    put(sock, msg, sizeof(msg));
    memset(stringPtr, 0, DATE_SIZE);
    get(sock, stringPtr, DATE_SIZE);
}

void askForMemberNum(int sock, char * numPtr, unsigned char size) {
    unsigned char msg[40];

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter number of members:\n");
    put(sock, msg, sizeof(msg));
    memset(numPtr, 0, sizeof(unsigned char));
    get(sock, numPtr, sizeof(unsigned char));
}

void doSomethingWithName(char * name)
{
    printf("Received name from the client: %s\n", name);
}
