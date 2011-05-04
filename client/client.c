#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

#include "client.h"

#define PORT 9876
//#define PORT_SERVER 9350

void put(vkvsserver* server, char* k, char* value)
{
	connect(server);
	

}

void send(vkvsserver* server, char* buffer, int size)
{
	//3.send
	printf("3. send\n");
	printf("\nEnter message that you want to send:\n");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	n = write(initsock, buffer, strlen(buffer));
	if(n<0)	{
		printf("error writing to socket\n");
	}
	bzero(buffer, 256);
	n = read(initsock, buffer, 255);
	if(n<0)	{
		printf("error reading from socket\n");
	}
	printf("Message received from server: %s\n", buffer);
	return 0;
}


void connect(vkvsserver* server)	//why argc and argv can be optional? if absence, enter command with arg will generate error?
{
	int initsock;
	struct sockaddr_in srvaddr;
	struct hostent *server;
	char buffer[256];
	int n;
	int srvport;

	//1.create

	printf("1. create\n");
	initsock = socket(AF_INET, SOCK_STREAM, 0);
	if(initsock<0)	{
		printf("error opening socket\n");
	}

	server = gethostbyname(argv[1]);	//why no error this line when not including netdb.h???
	if(server==NULL)	{
		printf("error get host by name\n");
		exit(0);
	}
	bzero((char*)&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	//printf("%d",sizeof(server->h_addr));
	bcopy((char *)(server->h_addr), (char *)&srvaddr.sin_addr.s_addr, server->h_length);

	srvport = atoi(argv[2]);
	srvaddr.sin_port = htons(srvport);

	//2.connect
	printf("2. connect\n");
	if(connect(initsock, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) < 0)	{
		printf("error connecting\n");
	}

}
