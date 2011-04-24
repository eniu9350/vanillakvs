#include "cmdserver.h"
#include "kvs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


struct cmdserver {
	int port;
};

cmdserver server;
table* maintb = NULL;

/*
   argv[1] --- port number
 */
int main(int argc, char* argv[])
{
	printf("main 1\n");
	server.port = atoi(argv[1]);

	printf("main 2\n");
	tableInit(&maintb);

	printf("main 3\n");
	mainloop();

}


void mainloop()
{
	int initsock, accsock;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t clilen;
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
	servaddr.sin_port = htons(server.port);
	if(bind(initsock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)	{
		printf("error on binding\n");
	}

	//3. listen
	listen(initsock, 5);
	printf("listening ...\n");
	clilen = sizeof(cliaddr);

	//4. accept
	while(1)	{
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
		processCmd(buffer, n);
		n = write(accsock, "this is an echo msg from lubuntuhm_root, port 9350", 50);
		if(n<0)	{
			printf("error writing to socket\n");
		}	
	}

}

void processCmd(char* buffer, int n)
{
	char key[20];
	char value[20];

	char* tmp = (char*)malloc(256);
	strncpy(tmp, buffer, n);
	tmp[255] = '\0';
	char* p = tmp+1;
	char* q;
	printf("pc 1\n");
	while(*p!='|')	{
		p++;
	}	
	printf("pc 2\n");
	puts(buffer);
	strncpy(key, tmp+1, p-tmp-1);
	key[p-tmp-1] = '\0';
	q = p+1;
	printf("pc 3\n");
	while(*q!='|')	{
		q++;
	}
	printf("pc 4\n");
	strncpy(value, p+1, q-p-1);
	value[q-p-1] = '\0';
	printf("pc 5\n");
	printf("in procCMD, key = %s\n", key);
	printf("in procCMD, value = %s\n", value);
}
