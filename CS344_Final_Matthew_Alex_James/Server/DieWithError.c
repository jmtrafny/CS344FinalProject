/*
	Author:  DGB
	Date: 4/27/2019
	Program: DieWithError.c

	Description:

		Prints error message in human readable form.
*/
#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
