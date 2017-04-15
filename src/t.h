#ifndef T_H
#define T_H

/*** includes ***/

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE


#include "abuf.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

/*** macros & defs ***/

#define CTRL_KEY(k) ((k) & 0x1f)
#define T_VERSION "0.0.1"

/*** data ***/

//enums auto increment
enum editorKey{
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	DEL_KEY,
	HOME_KEY,
	END_KEY,
	PAGE_UP,
	PAGE_DOWN
};

typedef struct erow{
	int size;
	char * chars;
} erow;

struct editorConfig{
	int cx;
	int cy;
	int rowoff;
	int coloff;
	int screenrows;
	int screencols;
	int numrows;
	erow *row;
	struct termios orig_termios;
};

struct editorConfig E;

/*** terminal ***/

void die(const char*);
void disableRawMode();
int editorReadKey();
void enableRawMode();
int getCursorPosition(int*, int*);
int getWindowSize(int*, int*);

/*** row ops ***/

void editorAppendRow(char*, size_t);

/*** file i/o ***/

void editorOpen(char*);

/*** output ***/

void editorClearScreen(struct abuf*);
void editorDrawRows(struct abuf*);
void editorRefreshScreen();
void editorScroll();

/*** input ***/

void editorMoveCursor(int);
void editorProcessKeypress();

/*** init ***/

void initEditor();

#endif
