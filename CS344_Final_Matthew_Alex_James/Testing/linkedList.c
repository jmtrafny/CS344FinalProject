#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "projectStructure.h"

//void append(LINKED_LIST * listPtr, struct * project);
void append(LINKED_LIST * listPtr, void * data)
{
	//int * dataCopy = (int *)malloc(sizeof(int));
	//dataCopy = data;
	if (data == NULL) return;
	/*get a node to put on the list and add the data to it */
	LIST_NODE * node = (LIST_NODE *) malloc(sizeof(LIST_NODE));
	node->dataPtr = data;//dataCopy;
	node->next = NULL;
	node->prev = NULL;

	listPtr->size++;
	if(listPtr->front == NULL) /* See if it's the first to go on the list */
	{
		listPtr->front = listPtr->back = node;
		return;
	}
	
	listPtr->back->next = node;
	node->prev = listPtr->back;
	listPtr->back = node;
}

void prepend(LINKED_LIST * listPtr, void * data)
{
	if (data == NULL) return;
	/*get a node to put on the list and add the data to it */
	LIST_NODE * node = (LIST_NODE *) malloc(sizeof(LIST_NODE));
	node->dataPtr = data;
	node->next = NULL;
	node->prev = NULL;

	listPtr->size++;
	if(listPtr->front == NULL) /* See if it's the first to go on the list */
	{
		listPtr->front = listPtr->back = node;
		return;
	}
	
	listPtr->front->prev = node;
	node->next = listPtr->front;
	listPtr->front = node;
}

//int insert(LINKED_LIST * listPtr, struct * project, int position);
int insert(LINKED_LIST * listPtr, void * data, int position){
	// Setup pointers
	LIST_NODE * tmpPtr = listPtr->front;
	LIST_NODE * newNode = (LIST_NODE *) malloc(sizeof(LIST_NODE));
	newNode->dataPtr = data;
	newNode->next = NULL;
	newNode->prev = NULL;

	// Edge cases
	if (listPtr->size == 0){ return -1; }
	if (position < 0 || position > listPtr->size){ return -1; }
	if (position == 0){ 
		prepend(listPtr, data);
		//prepend already increases size
		//listPtr->size++;
		return 0;
	}
	if (position == listPtr->size){ 
		append(listPtr, data); 
		//append already increases size
		//listPtr->size++;
		return 0;
	}

	// Traverse to insert location
	int i; // for loop counter
	for(i = 0; i < position; i++){
		tmpPtr = tmpPtr->next;
	}

	// Insert node
	newNode->prev = tmpPtr->prev;
	newNode->next = tmpPtr;
	tmpPtr->prev->next = newNode;
	tmpPtr->prev = newNode;

	// Clean up
	listPtr->size++;
	//free(tmpPtr);
	return 0;
}

/*
 * Function:  removeFromFront 
 * --------------------
 * Takes in a linked list and removes the front node 
 *
 *  listPtr: pointer to list to manipulate
 *
 *  returns: pointer to data held by deleted node
 */
void * removeFromFront(LINKED_LIST * listPtr){
	LIST_NODE * tmpPtr = listPtr->front;
	void * tempData = tmpPtr->dataPtr;

	// Edge cases
	if (listPtr->size == 0) return NULL;
	if (listPtr->front == listPtr->back) {
		listPtr->size--;
		listPtr->front = listPtr->back = NULL;
		return tempData;
	}
	
	// There are two or greater nodes in list
	listPtr->front = listPtr->front->next;
	listPtr->front->prev = NULL;
	free(tmpPtr);
	
	listPtr->size--;
	return tempData;
}

/*
 * Function:  removeFromBack 
 * --------------------
 * Takes in a linked list and removes the rear node 
 *
 *  listPtr: pointer to list to manipulate
 *
 *  returns: pointer to data held by deleted node
 */
void * removeFromBack(LINKED_LIST * listPtr){
	LIST_NODE * tmpPtr = listPtr->back;

	// Edge cases
	if (listPtr->size == 0) return NULL;
	if (listPtr->front == listPtr->back) {
		listPtr->back = NULL;
	}
	
	void * tempData = tmpPtr->dataPtr;

	// There are two or greater nodes in list
	listPtr->back = listPtr->back->prev;
	listPtr->back->next = NULL;
	free(tmpPtr);
	
	listPtr->size--;
	return tempData;
}

//void * removeAtPosition(LINKED_LIST * listPtr, int position);
void * removeAtPosition(LINKED_LIST * listPtr, int position){
	// Setup pointers
	LIST_NODE * tmpPtr = listPtr->front;
	void * tempData;

	// Edge cases
	if (listPtr->size == 0){ return NULL; }
	if (position < 0 || position >= listPtr->size){ return NULL; }
	if (position == 0){ 
		removeFromFront(listPtr);
		//removeFromFront already reduces size
		//listPtr->size--;
		return 0;
	}
	if (position == listPtr->size-1){ 
		removeFromBack(listPtr); 
		//removeFromFront already reduces size
		//listPtr->size--;
		return 0;
	}

	// Traverse to insert location
	int i; // for loop counter
	for(i = 0; i < position; i++){
		tmpPtr = tmpPtr->next;
	}
	tempData = tmpPtr->dataPtr;

	// Remove node
	tmpPtr->prev->next = tmpPtr->next;
	tmpPtr->next->prev = tmpPtr->prev;

	// Clean up
	listPtr->size--;
	free(tmpPtr);
	return tempData;
}

// For displaying project to consol
void printProject(void * dataPtr){
	PROJECT_STRUCT * ps = (PROJECT_STRUCT *) dataPtr;
	printf("Project ID: %d\n", ps->proj_id);
	printf("Project Description: %s\n", ps->proj_desc);
	printf("Date Created: %s\n", ps->proj_date_created);
	printf("Due Date: %s\n", ps->proj_date_due);
	printf("Number of Members: %d\n", ps->proj_num_members);
	printf("Members:\n");
	traverseForward(ps->proj_member_list, displayMembers);
}

void sendToFile(LINKED_LIST * listPtr, FILE * outFile){
	// Access first node in our list
	LIST_NODE * front = listPtr->front;
	PROJECT_STRUCT * ps = (PROJECT_STRUCT *) malloc(sizeof(PROJECT_STRUCT));
	LINKED_LIST member_list;
	LIST_NODE * member_node;

	// open file, write size of list
	outFile = fopen("out.file", "w");
	fprintf(outFile, "%d\n", listPtr->size);
	
	while(front){
		// Get project from current node
		ps = (PROJECT_STRUCT *) front->dataPtr;
		member_list = ps->proj_member_list;
		member_node = member_list.front;

		// Write contents to file
		fprintf(outFile, "%d\n", ps->proj_id);
		fprintf(outFile, "%s\n", ps->proj_desc);
		fprintf(outFile, "%s\n", ps->proj_date_created);
		fprintf(outFile, "%s\n", ps->proj_date_due);
		fprintf(outFile, "%d\n", ps->proj_num_members);
		// Go through members
		while(member_node){
			char * arr = member_node->dataPtr;
			fprintf(outFile, "%s\n", arr);
			//printf("%s\n", arr);
			member_node = member_node->next;
		}

		// Go to next node
		front = front->next;
	}
	
	fclose(outFile);
}

LINKED_LIST * loadFromFile(){
	// Create project list that will be returned
	LINKED_LIST * project_list = (LINKED_LIST *) malloc(sizeof(LINKED_LIST));
	project_list->size = 0;
	project_list->front = project_list->back = NULL;

	// Create file pointer and open file
	FILE * fp;
	char fname[100] = "";
	printf("\n\nPlease enter file name to load from: \n");
	scanf("%s",&fname);
	fp = fopen(fname,"r");
        if(fp == NULL)
	{
		printf("\n%s\" File NOT FOUND!", fname);
		return project_list;
	}

	// File is now open, can now read through file to fill in project struct
	char * line = NULL;
	char * p;
	size_t len = 0;
	ssize_t read;

	// Get first integer in file; that is the number of projects.
	read = getline(&line, &len, fp);
	unsigned int num_of_projects = atoi(line);
	printf("%d projects found!\n", num_of_projects);

	// Outer loop of reading loop, one for each project
	int i = 0; // for loop outer index
	for(i = 0; i < num_of_projects; i++){
		// Create project structure and start filling it in
		PROJECT_STRUCT * ps = (PROJECT_STRUCT *) malloc(sizeof(PROJECT_STRUCT));
		//--------------------------------------
		read = getline(&line, &len, fp);      // proj_id
		ps->proj_id = atoi(line);			  

		read = getline(&line, &len, fp);      // proj_desc
		strncpy(ps->proj_desc, line, read-1);

		read = getline(&line, &len, fp);      // proj_date_created
		strncpy(ps->proj_date_created, line, read-1);

		read = getline(&line, &len, fp);      // proj_due_date
		strncpy(ps->proj_date_due, line, read-1);

		read = getline(&line, &len, fp);      // proj_num_members
		ps->proj_num_members = atoi(line);	  

		LINKED_LIST member_list;// = (LINKED_LIST *) malloc(sizeof(LINKED_LIST));
		member_list.size = 0;
		member_list.front = member_list.back = NULL;

		int j = 0; // for loop inner index
		for(j = 0; j < ps->proj_num_members; j++){
			// Add members to members linked list
			read = getline(&line, &len, fp);
			line[strlen(line)-1] = '\0';
			printf("reading: %s\n", line);
			append(&member_list, line);
		}	
		//--------------------------------------
		// Now attach the linked list we just made to the proj
		ps->proj_member_list = member_list;
		printf("printing memberlist:\n");
		traverseForward(ps->proj_member_list, displayMembers);
		//printf("Printing project %d\n", ps->proj_id);
		//printProject(ps);
		// Add project to list to be returned
		append(project_list, ps);
	}

	free(line);
	fclose(fp);
	printf("***Leaving loadFromFile()\n");
	return project_list;
}

//void display(struct * project);
// Author: DBG
void display(void * data)
{
	int * ptr = (int *) data;
	printf("%d\n",  *ptr);
}

void displayMembers(void * dataPtr){
	char * arr = dataPtr;
	printf("%s\n", arr);
}

void displayProjID(void * dataPtr){
	PROJECT_STRUCT * ps = (PROJECT_STRUCT *) dataPtr;
	printf("%d\n", ps->proj_id); 
}

void displayProjDesc(void * dataPtr){
	PROJECT_STRUCT * ps = (PROJECT_STRUCT *) dataPtr;
	printf("%s\n", ps->proj_desc); 
}

// Author: DBG
void traverseForward(LINKED_LIST head, void function(void *))
{
	LIST_NODE * front = head.front;
	while(front)
	{
		function(front->dataPtr);
		front = front->next;
	}
}


// Author: DBG
void traverseBackward(LINKED_LIST head, void function(void *))
{
	LIST_NODE * back = head.back;
	while(back)
	{
		function(back->dataPtr);
		back = back->prev;
	}
}

