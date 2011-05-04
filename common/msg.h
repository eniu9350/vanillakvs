

#define MSG_SEP '|'

#define MT_PUT 0

char* packmsg_put(const char* k, const char* v, int* len);

void unpackmsg_put(char* msg, int len, char** k, char** v);
