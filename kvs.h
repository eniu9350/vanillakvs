#ifndef _VKVS_KVS_H_
#define _VKVS_KVS_H_


typedef struct tableEntry	{
	char* key;
	char* value;
	struct tableEntry* next;
}tableEntry;

typedef struct table	{
	unsigned int size;
	tableEntry* head;
	tableEntry* tail;
}table;


void tableInit(table** t);
char* tableGet(table* t, char* key);
void tablePut(table* t, char* key, char* value);

#endif
 
