#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../HeaderFiles/linkedList.h"
#include "../HeaderFiles/projectStructure.h"

#define DESC_SIZE 1001 //project description size
#define DATE_SIZE 9 //project date created and due size

void createProject(int sock, PROJECT_STRUCT * project) {
    askForProjectID(sock, &project->proj_id, sizeof(int));
    printf("This is the project ID: %d\n", project->proj_id);

    askForProjectDescription(sock, project->proj_desc, DESC_SIZE);
    printf("This is the project description: %s\n", project->proj_desc);

    askForProjectDateCreated(sock, project->proj_date_created, DATE_SIZE);
    printf("This is the project creation date: %s\n", project->proj_date_created);

    askForProjectDateDue(sock, project->proj_date_due, DATE_SIZE);
    printf("This is the project due date: %s\n", project->proj_date_due);

    printf("Before askForNumMembers\n");
    askForMemberNum(sock, project->proj_num_members, sizeof(unsigned char));
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

void askForMemberNum(int sock, char memNum, unsigned int size) {
    unsigned char msg[40];

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter number of members:\n");
    put(sock, msg, sizeof(msg));
    get(sock, &memNum, size);
}
