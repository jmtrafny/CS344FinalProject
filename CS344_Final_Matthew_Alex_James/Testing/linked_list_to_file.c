#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"
#include "projectStructure.h"

int main(int argc, char *argv[])
{
	char member1[] = "James";
	char member2[] = "Stephanie";
	char member3[] = "Lilly"; 
	char member4[] = "Olive";

	// Create project linkedlist
	LINKED_LIST project_list;
	project_list.size = 0;
	project_list.front = project_list.back = NULL;
		// Create member linkedlist for proj 1
	LINKED_LIST project_1_member_list;
	project_1_member_list.size = 0;
	project_1_member_list.front = project_1_member_list.back = NULL;
		// Create member linkedlist for proj 2
	LINKED_LIST project_2_member_list;
	project_2_member_list.size = 0;
	project_2_member_list.front = project_2_member_list.back = NULL;

	// Create struct for first proj
	PROJECT_STRUCT * ps1 = (PROJECT_STRUCT *) malloc(sizeof(PROJECT_STRUCT));
	ps1->proj_id = 1;																// Project ID
	strncpy(ps1->proj_desc, "Description of project 1.", sizeof(ps1->proj_desc));	// Project Description
	strncpy(ps1->proj_date_created, "04102019", sizeof(ps1->proj_date_created));	// Creation date
	strncpy(ps1->proj_date_due, "04252019", sizeof(ps1->proj_date_due));			// Due date
	append(&project_1_member_list, &member1);
	append(&project_1_member_list, &member2);
	ps1->proj_num_members = project_1_member_list.size;								// Number of members
	ps1->proj_member_list = project_1_member_list;									// Member list

	// Create struct for second proj
	PROJECT_STRUCT * ps2 = (PROJECT_STRUCT *) malloc(sizeof(PROJECT_STRUCT));
	ps2->proj_id = 2;
	strncpy(ps2->proj_desc, "Description of project 2.", sizeof(ps2->proj_desc));
	strncpy(ps2->proj_date_created, "03092018", sizeof(ps2->proj_date_created));
	strncpy(ps2->proj_date_due, "06102018", sizeof(ps2->proj_date_due));
	append(&project_2_member_list, &member3);
	append(&project_2_member_list, &member4);
	ps2->proj_num_members = project_2_member_list.size;
	ps2->proj_member_list = project_2_member_list;

	// Add project structs to project list	
	append(&project_list, ps1);
	append(&project_list, ps2);
	
	//-----------------------------------------------
	// Display all project IDs
	//traverseForward(project_list, displayProjID);
	//-----------------------------------------------
	// Display all project Descriptions
	//traverseForward(project_list, displayProjDesc);
	//-----------------------------------------------
	// Display members of each project
	//printf("Member of project 1: \n");
	//traverseForward(project_1_member_list, displayMembers);
	//printf("Member of project 2: \n");
	//traverseForward(project_2_member_list, displayMembers);
	//-----------------------------------------------
	// Display all project info
	//printf("\nPrinting Project 1 info:\n");
	//printProject(ps1);
	//printf("\nPrinting Project 2 info:\n");
	//printProject(ps2);
	//-----------------------------------------------
	// Display all projects from list
	FILE * fp;
	sendToFile(&project_list, fp);
	
	printf("ok\n");
	
	return 0;
}