#include "cmdserver.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>

#define PORT 9350

int main()
{
	int initsock, accsock;
	struct sockaddr_in servaddr, cliaddr;
	int clilen;
	char buffer[256];
	int n;

	//1. create socket
	initsock = socket(AF_INET, SOCK_STREAM, 0);
	if(initsock<0)	{
		printf("initsock error\n");
	}

	//2. bind
	bzero((char *) &servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	if(bind(initsock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)	{
		printf("error on binding\n");
	}

	//3. listen
	listen(initsock, 5);
	printf("listening ...\n");
	clilen = sizeof(cliaddr);

	//4. accept
	accsock = accept(initsock, (struct sockaddr*)&cliaddr, &clilen);
	if(accsock < 0)	{
		printf("error on accept\n");
	}
	printf("accept end \n");
	//block here?

	//5. read
	bzero(buffer, 256);

	n = read(accsock, buffer, 255);
	if(n<0)	{
		printf("error reading from socket\n");
	}
	printf("\nin >>>buffer>>> : %s\n", buffer);
	n = write(accsock, "this is an echo msg from lubuntuhm_root, port 9350");
	if(n<0)	{
		printf("error writing to socket\n");
	}	



	return 0;
}
