#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"


int insert(LINKED_LIST * listPtr, struct * project, int position) {
    int i = 0;

    if((position < 0) || (position > listPtr->size)) {
        return -1;
    }

    LIST_NODE * node = (LIST_NODE *) calloc(1, sizeof(LIST_NODE));
    node->next = node->prev = NULL;
    node->projectPtr = project;

    if (position == 0) {
        node->next = listPtr->front;
        node->prev = NULL;
        listPtr->front->prev = node;
        listPtr->front = node;
        listPtr->size++;
        return 0;
    }

    if (position == listPtr->size) {
        node->prev = listPtr->back;
        node->next = NULL;
        listPtr->back->next = node;
        listPtr->back = node;
        listPtr->size++;
        return 0;
    }

    LIST_NODE * currNode = listPtr->front;

    for(i=0;i<position;i++){
        currNode = currNode->next;
    }
    node->next = currNode;
    node->prev = currNode->prev;
    currNode->prev->next = node;
    currNode->prev = node;
    listPtr->size++;
    return 0;

}

void * removeAtPosition(LINKED_LIST * listPtr, int position) {
    int i = 0;
    if(position < 0 || position >= listPtr->size) {
        return NULL;
    }

    LIST_NODE * currNode = listPtr->front;
    void * projectPointer = currNode->projectPtr;

    if(position == 0){
        listPtr->front = currNode->next;
        listPtr->front->prev = NULL;
        currNode->prev = currNode -> next = NULL;
        free(currNode->projectPtr);
        free(currNode);
        listPtr->size--;
        return projectPointer;
    }

    if(position == listPtr->size - 1) {
        currNode = listPtr->back;
        projectPointer = currNode->projectPtr;
        listPtr->back = currNode->prev;
        listPtr->back->next = NULL;
        currNode->prev = currNode->next = NULL;
        free(currNode->projectPtr);
        free(currNode);
        listPtr->size--;
        return projectPointer;
    }

    for(i=0;i<position;i++){
        currNode = currNode->next;
    }

    projectPointer = currNode->projectPtr;
    currNode->prev->next = currNode->next;
    currNode->next->prev = currNode->prev;
    currNode->next = currNode->prev = NULL;
    free(currNode->projectPtr);
    free(currNode);
    listPtr->size--;
    return projectPointer;
}

//TODO: update the field names for the project structure so display() works
void display(struct * project) {
	printf("Project name: %s\n"
        "Project description: %s\n"
        "Project date: %s\n"
        "Project due date: %s\n"
        "Number of members: %c\n" //a BYTE that will keep track of number of members
        "Project member names: %s\n",
        project->name,
        project->description,
        project->date,
        project->dueDate,
        project->memberSize,
        project->memberNames);
}

void traverseForward(LINKED_LIST head, void function(void *)) {
	LIST_NODE * front = head.front;
	while(front)
	{
		function(front->projectPtr);
		front = front->next;
	}
}

void traverseBackward(LINKED_LIST head, void function(void *)) {
	LIST_NODE * back = head.back;
	while(back)
	{
		function(back->projectPtr);
		back = back->prev;
	}
}

void append(LINKED_LIST * listPtr, struct * project) {
	if (project == NULL) return;
	/*get a node to put on the list and add the project to it */
	LIST_NODE * node = (LIST_NODE *) malloc(sizeof(LIST_NODE));
	node->projectPtr = project;
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
