#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../HeaderFiles/menu.h"
#include "../HeaderFiles/linkedList.h"
#include "../HeaderFiles/projectStructure.h"

#define DESC_SIZE 1001 //project description size
#define DATE_SIZE 9

unsigned int sendProjectDataAndWaitForResponse(int clntSocket);

void editProject(int sock, LINKED_LIST * projectList) {
    int answer;
    unsigned char errorMsg[] = "Invalid Choice";
    PROJECT_STRUCT * project = (PROJECT_STRUCT *) projectList->front->dataPtr;
    //printProject(project);
    answer = sendProjectDataAndWaitForResponse(sock);
    while(answer != 6)
    {
        switch(answer)
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
            	askForProjectDateDue(sock, project->proj_date_due, DATE_SIZE);
                break;
            case 5:
            	printf("Client is editing project member number.\n");
            	askForMemberNum(sock, project->proj_num_members, sizeof(unsigned char));
                break;
            case 6:
                printf("Client has stopped editing.\n");
                break;
            default:
            	printf("Client selected junk.\n");
            	put(sock, errorMsg, sizeof(errorMsg));
            	break;
        }
        answer = sendProjectDataAndWaitForResponse(sock);
        printf("This is the answer: %d", answer);
    }//end while





}

unsigned int sendProjectDataAndWaitForResponse(int clntSocket) {
    MENU projectData;
    unsigned int answer = 0;
    memset(&projectData, 0, sizeof(MENU));   /* Zero out structure */
    strcpy(projectData.option1,"1) Project ID\n");
    strcpy(projectData.option2, "2) Project description\n");
    strcpy(projectData.option3, "3) Project creation date\n");
    strcpy(projectData.option4, "4) Project due date\n");
    strcpy(projectData.option5, "5) Project member number\n");
    strcpy(projectData.option6, "6) Exit\n");
    printf("Sending menu\n");
    put(clntSocket, &projectData, sizeof(MENU));
    get(clntSocket, &answer, sizeof(unsigned int));
    return ntohl(answer);
}

