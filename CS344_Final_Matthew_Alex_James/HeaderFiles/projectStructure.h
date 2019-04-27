/*
	Author:  Alex Hall
			 Matthieu Privat
			 James Trafny
	Date: 4/27/2019
	Program: projectStructure.h

	Description:

		Hedder file project structures.
*/

#ifndef PROJECT_STRUCTURE_H
#define PROJECT_STRUCTURE_H

#include "linkedList.h"

typedef struct project_struct{
	int proj_id;
	char proj_desc[1000];
	char proj_date_created[9];
	char proj_date_due[9];
	unsigned char proj_num_members;
	LINKED_LIST * proj_member_list;
} PROJECT_STRUCT;

typedef struct{
	unsigned int x;
	unsigned int y;
 	unsigned char oper;
} TRANS_DATA_TYPE;

typedef struct{
	unsigned int x;
 	unsigned int y;
} DATA_TYPE;


PROJECT_STRUCT * createProject(int sock);
void askForProjectID(int sock, int * numPtr, unsigned int size);
void askForProjectDescription(int sock, char * stringPtr, unsigned int size);
void askForProjectDateCreated(int sock, char * stringPtr, unsigned int size);
void askForProjectDateDue(int sock, char * stringPtr, unsigned int size);
void askForMemberNum(int sock, char memNum, unsigned int size);

#endif //PROJECT_STRUCTURE_H
