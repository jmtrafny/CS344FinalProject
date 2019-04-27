/*
Authors: Dr. Bethelmy
Edited: Alex Hall, James Trafny
Date: 27 April, 2019
File: transmission.c

This file runs the transmission between the server and client,
and keeps track of the bytes sent between the two.
*/

#include <sys/socket.h> /* for recv() and send() */
void DieWithError(char *errorMessage);  /* Error handling function */

/*
Function: get()
-----------------------------
This method receives bytes from the sender 
and tallies the total amount of bytes received.
It also will terminate if there is an error by 
calling DieWithError()

totalBytesRcvd: An unsigned integer that counts the total
                amount of bytes received
bytesRcvd: An unsigned integer that counts the amount of 
           bytes received in any single transmission

returns: void
*/

void get(int sock, void * buffer, unsigned int size)
{
  unsigned int totalBytesRcvd = 0;
  unsigned int bytesRcvd = 0;

  while(totalBytesRcvd < size)
  {
     if((bytesRcvd = recv(sock, buffer+bytesRcvd, size, 0)) <= 0)
       DieWithError("recv() failed or connection closed prematurely");
     totalBytesRcvd += bytesRcvd;
  }
}

/*
Function: put()
-----------------------------
A method that terminates the program if the received
buffer is not equal to the size of the message.

returns: void
*/

void put(int sock, void * buffer, unsigned int size)
{
    if (send(sock, buffer, size, 0) != size)
        DieWithError("send() failed");
}

