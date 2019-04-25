
#ifndef PROJECT_H
#define PROJECT_H


void createProject(int sock, PROJECT_STRUCT * project);
void askForProjectID(int sock, int * numPtr, unsigned int size)
void askForProjectDescription(int sock, char * stringPtr, unsigned int size);
void askForProjectDateCreated(int sock, char * stringPtr, unsigned int size);
void askForProjectDateDue(int sock, char * stringPtr, unsigned int size);
void askForMemberNum(int sock, char * numPtr, unsigned char size);

#endif
