#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "linkedList.h"
#include "projectStructure.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */
#define NAME_SIZE 21 /*Includes room for null */
#define DESC_SIZE 1001 //project description size
#define DATE_SIZE 9 //project date created and due size


void DieWithError(char *errorMessage);  /* Error handling function */
void get(int, void *, unsigned int);
void put(int, void *, unsigned int);
char * getPassword(int clntSocket);
char * getUsername(int clntSocket);

/*
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
*/

void login(int clntSocket)
{
    printf("In login fucntion");
    int recvMsgSize;                    /* Size of received message */
    char * username = (char *) calloc(50, sizeof(char));
    char * password = (char *) calloc(50, sizeof(char));

    unsigned char name[NAME_SIZE]; //max length 20
    int number = 0;
    unsigned char errorMsg[] = "Invalid Choice";
    unsigned char bye[] = "Bye!";

    username = getUsername(clntSocket);
    password = getPassword(clntSocket);

    printf("%s, %s", username, password);

    put(clntSocket, bye, sizeof(bye));
    close(clntSocket);    /* Close client socket */
    printf("Connection with client %d closed.\n", clntSocket);
}

void createAccount(int clntSocket)
{
    printf("in createAccount");
    int recvMsgSize;                    /* Size of received message */
    char * username = (char *) calloc(50, sizeof(char));
    char * password = (char *) calloc(50, sizeof(char));

    unsigned char name[NAME_SIZE]; //max length 20
    int number = 0;
    unsigned char errorMsg[] = "Invalid Choice";
    unsigned char bye[] = "Bye!";

    username = getUsername(clntSocket);
    password = getPassword(clntSocket);

    printf("%s, %s", username, password);

    put(clntSocket, bye, sizeof(bye));
    close(clntSocket);    /* Close client socket */
    printf("Connection with client %d closed.\n", clntSocket);
}

char * getUsername(int clntSocket) {
    MENU mainMenu;
    char * response = (char *) calloc(50, sizeof(char));
    memset(&mainMenu, 0, sizeof(MENU));   /* Zero out structure */
    strcpy(mainMenu.option1, "1) Enter Username:\n");
    strcpy(mainMenu.option2, "\n");
    strcpy(mainMenu.option3, "\n");
    strcpy(mainMenu.option4, "\n");
    strcpy(mainMenu.option5, "\n");
    strcpy(mainMenu.option6, "\n");
    printf("Sending menu\n");
    put(clntSocket, &mainMenu, sizeof(MENU));
    //get(clntSocket, &response, sizeof(char)*50);
    get(clntSocket, &response, sizeof(unsigned int));
    //return ntohl(response);
    return response;
}

char * getPassword(int clntSocket) {
    MENU mainMenu;
    char * response = (char *) calloc(50, sizeof(char));
    memset(&mainMenu, 0, sizeof(MENU));   /* Zero out structure */
    strcpy(mainMenu.option1, "1) Enter Password:\n");
    strcpy(mainMenu.option2, "\n");
    strcpy(mainMenu.option3, "\n");
    strcpy(mainMenu.option4, "\n");
    strcpy(mainMenu.option5, "\n");
    strcpy(mainMenu.option6, "\n");
    printf("Sending menu\n");
    put(clntSocket, &mainMenu, sizeof(MENU));
    //get(clntSocket, &response, sizeof(char)*50);
    get(clntSocket, &response, sizeof(unsigned int));
    //return ntohl(response);
    return response;
}