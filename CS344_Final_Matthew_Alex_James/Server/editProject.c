/*
    Author:  Alex Hall
    Date: 4/27/2019
    Program: DieWithError.c

    Description:

        Server side for editing a project.  Requires the
        client socket and also a LINKED_LIST of project
        structures to index into.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../HeaderFiles/menu.h"
#include "../HeaderFiles/linkedList.h"
#include "../HeaderFiles/projectStructure.h"

#define DESC_SIZE 1001 //project description size
#define DATE_SIZE 9

/*
 * Function:  editProject 
 * --------------------
 * Takes in a user socket and position within the list
 * of projects to which project will be edited
 *
 *  sock: client socket
 *  position: position within the linked list to edit
 *            0 = position 1
 *
 *  returns: the edited PROJECT_STRUCT *
 */
PROJECT_STRUCT * editProject(int sock, int position) {
    PROJECT_STRUCT * project;

    printProject(project);
    response = sendProjectDataAndWaitForResponse(sock);
    while(response != 6)
    {
        switch(response)
        {
            case 1:
            	printf("Client is editing project ID.\n");

            	askForProjectID(sock, &project->proj_id, sizeof(int));
                break;
            case 2:
            	printf("Client is editing project description.\n");

            	askForProjectDescription(sock, project->proj_desc, DESC_SIZE);
                break;
            case 3:
            	printf("Client is editing project creation date.\n");
            	askForProjectDateCreated(sock, project->proj_date_created, DATE_SIZE);
                break;
            case 4:
            	printf("Client is editing project due date.\n");
            	askForProjectDateDue(sock, project->proj_date_due, DATE_SIZE)
                break;
            case 5:
            	printf("Client is editing project member number.\n");
            	askForMemberNum(sock, project->proj_num_members, sizeof(unsigned char));
                break;
            default:
            	printf("Client selected junk.\n");
            	put(clntSocket, errorMsg, sizeof(errorMsg));
            	break;
        }
        response = sendProjectDataAndWaitForResponse(clntSocket);
    }//end while





}

/*
 * Function:  sendProjectDataAndWaitForResponse 
 * --------------------
 * Sends editing options to client
 *
 *  clntSocket: client socket
 *
 *  returns: menu item selected (int)
 */
int sendProjectDataAndWaitForResponse(int clntSocket) {
    MENU projectData;
    unsigned int response = 0;
    memset(&projectData, 0, sizeof(MENU));   /* Zero out structure */
    strcpy(projectData.option1,"1) Project ID\n");
    strcpy(projectData.option2, "2) Project description\n");
    strcpy(projectData.option3, "3) Project creation date\n");
    strcpy(projectData.option4, "4) Project due date\n");
    strcpy(projectData.option5, "5) Project member number\n");
    strcpy(projectData.option6, "6) Exit\n");
    printf("Sending menu\n");
    put(clntSocket, &projectData, sizeof(MENU));
    get(clntSocket, &response, sizeof(unsigned int));
    return ntohl(response);
}

