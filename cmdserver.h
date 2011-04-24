#ifndef _VKVS_CMDSERVER_H_
#define _VKVS_CMDSERVER_H_

struct cmdserver;

void mainloop();
void processCmd(char* msg, int n);



#endif
