#include <stdbool.h>

typedef struct {
	char* addr;
	int port;
	bool connected;
	int sockfd;
} vkvsserver;

void vkvs_put(vkvsserver* server, char* k, char* v);
void vkvs_send(vkvsserver* server, char* wbuf, int wbufsize);
void vkvs_connect(vkvsserver* server);	
