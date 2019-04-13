//Header file for doubly linked list type definitions and function declarations
//remember to use relative paths to include in other files -> #include "../LinkedList/linkedList.h"


#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list_node{
	void * dataPtr;
	struct list_node * next;
	struct list_node * prev;
} LIST_NODE;

typedef struct linkedList{
	int size;
	LIST_NODE * front, * back;
} LINKED_LIST;

void append(LINKED_LIST * listPtr, void * dataPtr);
int insert(LINKED_LIST * listPtr, void * dataPtr, int position);
void * removeAtPosition(LINKED_LIST * listPtr, int position);
void printProject(void *dataPtr);
void sendToFile(LINKED_LIST * listPtr, FILE * outfile);
void display(void * dataPtr);
void displayMembers(void * dataPtr);
void displayProjID(void * dataPtr);
void displayProjDesc(void * dataPtr);
void traverseForward(LINKED_LIST head, void function(void *));
void traverseBackward(LINKED_LIST head, void function(void *));


#endif // LINKED_LIST_H
