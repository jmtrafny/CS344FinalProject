
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



#endif //PROJECT_STRUCTURE_H