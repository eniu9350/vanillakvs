#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include "client.h"
#include "../common/msg.h"

#define PORT 9876
//#define PORT_SERVER 9350

int main()
{
		vkvsserver s;
		s.addr = "localhost";
		s.port = 9350;
		s.connected = 0;
		vkvs_put(&s, "name", "niujin");

}

void vkvs_put(vkvsserver* server, char* k, char* v)
{
		if(server->connected == 0)	{
				vkvs_connect(server);
		}
}

void vkvs_send(vkvsserver* server, char* wbuf, int wbufsize)
{
		int n; 
		//3.send
		printf("3. send\n");
		printf("\nEnter message that you want to send:\n");
		//bzero(buffer, 256);
		//fgets(buffer, 255, stdin);
		n = write(server->sockfd, wbuf, wbufsize);
		if(n<0)	{
				printf("error writing to socket\n");
		}

		char* rbuf = (char*)malloc(256);
		bzero(rbuf, 256);
		n = read(server->sockfd, rbuf, 255);
		if(n<0)	{
				printf("error reading from socket\n");
		}
		printf("Message received from server: %s\n", rbuf);
}


void vkvs_connect(vkvsserver* server)	//why argc and argv can be optional? if absence, enter command with arg will generate error?
{
		int initsock;
		struct sockaddr_in srvaddr;
		struct hostent *s;
		char buffer[256];
		int n;
		int srvport;

		//1.create

		printf("1. create\n");
		initsock = socket(AF_INET, SOCK_STREAM, 0);
		if(initsock<0)	{
				printf("error opening socket\n");
		}

		s = gethostbyname(server->addr);	//why no error this line when not including netdb.h???
		if(s==NULL)	{
				printf("error get host by name\n");
				exit(0);
		}
		bzero((char*)&srvaddr, sizeof(srvaddr));
		srvaddr.sin_family = AF_INET;
		//printf("%d",sizeof(server->h_addr));
		bcopy((char *)(s->h_addr), (char *)&srvaddr.sin_addr.s_addr, s->h_length);

		srvport = server->port;
		srvaddr.sin_port = htons(srvport);

		//2.connect
		printf("2. connect\n");
		if(connect(initsock, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) < 0)	{
				printf("error connecting\n");
		}

		server->sockfd = initsock;
		server->connected = true;

}
