//Header file for doubly linked list type definitions and function declarations
//remember to use relative paths to include in other files -> #include "../LinkedList/linkedList.h"


#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list_node{
	struct * projectPtr;
	struct list_node * next;
	struct list_node * prev;
} LIST_NODE;

typedef struct linkedList{
	int size;
	LIST_NODE * front, * back;
} LINKED_LIST;

int insert(LINKED_LIST * listPtr, struct * project, int position);
void * removeAtPosition(LINKED_LIST * listPtr, int position);
void display(struct * project);
void traverseForward(LINKED_LIST head, void function(void *));
void traverseBackward(LINKED_LIST head, void function(void *));
void append(LINKED_LIST * listPtr, struct * project);

#endif // LINKED_LIST_H
