#ifndef ABUF_H
#define ABUF_H

#include <string.h>

#define ABUF_INIT { NULL, 0}

struct abuf{
	char *b;
	int len;
};

void abAppend(struct abuf*, const char*, int);
void abFree(struct abuf*);

#endif
