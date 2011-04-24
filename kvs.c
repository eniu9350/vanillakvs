#include "kvs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_MAX_SIZE 1000
#define TABLE_INIT_SIZE 200
void tableInit(table** t)
{
	printf("in init 1");
	*t = (table*)malloc(sizeof(table));
	printf("in init 2");
	(*t)->size = TABLE_INIT_SIZE;
	printf("in init 3");
	(*t)->head = NULL;
	(*t)->tail = NULL;
}

char* tableGet(table* t, char* key)
{
	tableEntry* te = t->head;
	while(te!=NULL)	{
		if(strcmp(te->key, key)==0)	{
			return te->value;
		}
		te = te->next;
	}

	return NULL;
}

//should return error code?
void tablePut(table* t, char* key, char* value)
{
	printf("in put 1");

	tableEntry* te = t->head;
	tableEntry* newte;
	char* _key;
	char* _value;
	while(te!=NULL)	{
		if(strcmp(te->key, key)==0)	{
			break;
		}
		te = te->next;
	}

	printf("in put 2");

	if(te == NULL)	{
	printf("in put 3a");
		if(t->size == TABLE_MAX_SIZE)	{
			return;
		}
		else	{

			newte = (tableEntry*)malloc(sizeof(tableEntry));

			_key = (char*)malloc(strlen(key)+1);
			_value = (char*)malloc(strlen(value)+1);

			strcpy(_key, key);
			strcpy(_value, value);

			newte->key = key;
			newte->value = value;
			
			if(t->tail==NULL)	{
				t->head = newte;
				t->tail = newte;
				newte->next = NULL;
			}
			else{
				t->tail->next = newte;
				t->tail = newte;
				newte->next = NULL;
			}

			t->size++;
		}
	}
	else	{
	printf("in put 3b");
		_value = (char*)malloc(strlen(value)+1);
		strcpy(_value, value);
		te->value = _value;
	}
}

