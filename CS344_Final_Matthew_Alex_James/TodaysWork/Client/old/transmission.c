#include <sys/socket.h> /* for recv() and send() */
void DieWithError(char *errorMessage);  /* Error handling function */

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

void put(int sock, void * buffer, unsigned int size)
{
    if (send(sock, buffer, size, 0) != size)
        DieWithError("send() failed");
}

