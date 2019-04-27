/*
Author: Dr. Bethelmy
Date: 27 April, 2019
File: DieWithError.c

This file terminates the program when called with an error message.
*/

#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */

/*
Function: DieWithError()
---------------------------------
A method that will exit the program and print an error message.

returns: void
*/

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

// Test
// Change in new branch