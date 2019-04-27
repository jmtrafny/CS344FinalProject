/*
	Author:  Alex Hall
	Date: 4/27/2019
	Program: createProject.c

	Description:

		This file is used by the server to create and return a new
		project (PROJECT_STRUCT) to be added to project_list for 
		use in the server.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../HeaderFiles/linkedList.h"
#include "../HeaderFiles/projectStructure.h"

#define DESC_SIZE 1001 //project description size
#define DATE_SIZE 9 //project date created and due size

/*
 * Function:  createProject 
 * --------------------
 * Takes a socket and returns a new project to the caller.   
 *
 *  sock: client socket for use getting info from user
 *
 *  returns: PROJECT_STRUCT *
 */
PROJECT_STRUCT * createProject(int sock) {
    PROJECT_STRUCT * project = (PROJECT_STRUCT *) calloc (1, sizeof(PROJECT_STRUCT));
    LINKED_LIST * member_list = (LINKED_LIST *) calloc (1, sizeof(LINKED_LIST));

    askForProjectID(sock, &project->proj_id, sizeof(int));
    printf("This is the project ID: %d\n", project->proj_id);

    askForProjectDescription(sock, project->proj_desc, DESC_SIZE);
    printf("This is the project description: %s\n", project->proj_desc);

    askForProjectDateCreated(sock, project->proj_date_created, DATE_SIZE);
    printf("This is the project creation date: %s\n", project->proj_date_created);

    askForProjectDateDue(sock, project->proj_date_due, DATE_SIZE);
    printf("This is the project due date: %s\n", project->proj_date_due);

    askForMemberNum(sock, project->proj_num_members, sizeof(unsigned char));
    printf("This is the number of members: %d", project->proj_num_members);

    /*
    int i = 0;
    for(i = 0; i < project->proj_num_members; i++){
        askForMemberName();
    }
    */

    printf("leaving createProject()\n");
    return project;
}


/*
 * Function:  askForProjectID 
 * --------------------
 * Takes a socket, data pointer, and size of that pointer
 *  and asks to user for the ID of the project number.   
 *
 *  sock: client socket for use getting info from user
 *  numPtr: integer pointer for getting int id
 *  size: size of integer for get and put
 *
 *  returns: void
 */
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

/*
 * Function:  askForProjectDescription 
 * --------------------
 * Takes a socket, data pointer, and size of that pointer
 *  and asks to user for a description of the project.   
 *
 *  sock: client socket for use getting info from user
 *  stringPtr: char * pointer for getting description
 *  size: size of char * for get and put
 *
 *  returns: void
 */
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

/*
 * Function:  askForProjectDateCreated 
 * --------------------
 * Takes a socket, data pointer, and size of that pointer
 *  and asks to user for the creation date of the project.   
 *
 *  sock: client socket for use getting info from user
 *  stringPtr: char * pointer for getting date mmddyy
 *  size: size of char * for get and put
 *
 *  returns: void
 */
void askForProjectDateCreated(int sock, char * stringPtr, unsigned int size) {
    unsigned char msg[40];

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter project creation date:\n");
    put(sock, msg, sizeof(msg));
    memset(stringPtr, 0, DATE_SIZE);
    get(sock, stringPtr, DATE_SIZE);
}

/*
 * Function:  askForProjectDateDue 
 * --------------------
 * Takes a socket, data pointer, and size of that pointer
 *  and asks to user for the due date of the project.   
 *
 *  sock: client socket for use getting info from user
 *  stringPtr: char * pointer for getting due date mmddyy
 *  size: size of char * for get and put
 *
 *  returns: void
 */
void askForProjectDateDue(int sock, char * stringPtr, unsigned int size) {
    unsigned char msg[40];

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter project due date:\n");
    put(sock, msg, sizeof(msg));
    memset(stringPtr, 0, DATE_SIZE);
    get(sock, stringPtr, DATE_SIZE);
}

/*
 * Function:  askForMemberNum 
 * --------------------
 * Takes a socket, data pointer, and size of that pointer
 *  and asks to user for the number of members of the project.   
 *
 *  sock: client socket for use getting info from user
 *  stringPtr: char pointer for getting the number of members
 *  size: size of char for get and put
 *
 *  returns: void
 */
void askForMemberNum(int sock, char memNum, unsigned int size) {
    unsigned char msg[40];

    memset(msg, 0, sizeof(msg));
    strcpy(msg, "Enter number of members:\n");
    put(sock, msg, sizeof(msg));
    get(sock, &memNum, size);
}
