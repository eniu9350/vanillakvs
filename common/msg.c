#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "msg.h"

char* packmsg_put(const char* k, const char* v, int* len)
{
				printf("1");
				int nk = strlen(k);
				int nv = strlen(v);
				char* msg = (char*)malloc(nk+nv+5);     //size of key + size of value + size of 4 sep + size of type field
				printf("2");
				msg[0] = MSG_SEP;       //start with separator
				msg[1] = MT_PUT;
				msg[2] = MSG_SEP;       //start with separator
				msg[nk+3] = MSG_SEP;    
				msg[nk+nv+4] = MSG_SEP; //end with separator
				printf("3");
				memcpy(msg+3, k, nk);
				printf("4");
				memcpy(msg+nk+4, v, nv);
				printf("5");
				*len = nk+nv+5;

				return msg;
				return 0;
}

void unpackmsg_put(char* msg, int len, char** k, char** v)
{
				printf("start of up\n");

				char* p;
				char* s;
				p = msg+3;
				while(p-msg<len)	{
								if(*p==MSG_SEP)	{
												s = p;
												p++;
												break;
								}
								p++;
				}


				*k = (char*)malloc(s-msg-3+1);
				memcpy(*k, msg+3, s-msg-3);
				(*k)[s-msg-3] = 0;
				*v = (char*)malloc(msg+len-1-s-1+1);
				memcpy(*v, s+1, msg+len-1-s-1);
				(*v)[msg+len-1-s-1] = 0;	//mmm:!!!error without parentness!!!

}             
