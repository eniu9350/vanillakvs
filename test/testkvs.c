#include "../kvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	table* t;
	printf("1\n");	
	tableInit(&t);
	printf("2\n");	
/*
	char* key = (char*)malloc(20);
	strcpy(key, "time of #1 debug");
	char* value = (char*)malloc(20);
	strcpy(value, "23:45");
*/
	char key[] = "debug.2.time";
	char value[] = "00:28";
	printf("3\n");	
	tablePut(t, key, value);

	printf("after put\n");
	printf("get: key = \"%s\", value = \"%s\"", key, tableGet(t, key));
}
