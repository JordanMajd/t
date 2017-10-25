#ifndef T_H
#define T_H

/*** includes ***/

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE


#include "abuf.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

/*** macros & defs ***/

#define CTRL_KEY(k) ((k) & 0x1f)
#define T_VERSION "0.0.3"
#define T_TAB_STOP 8
#define T_QUIT_TIMES 3

/*** data ***/

//enums auto increment
enum editorKey{
	BACKSPACE = 127,
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

enum editorHighlight {
	HL_NORMAL = 0,
	HL_NUMBER,
	HL_MATCH
};

typedef struct erow{
	int size;
	int rsize;
	char *chars;
	char *render;
	unsigned char *hl;
} erow;

struct editorConfig{
	int cx;
	int cy;
	int rx;
	int rowoff;
	int coloff;
	int screenrows;
	int screencols;
	int numrows;
	erow *row;
	int dirty;
	char *filename;
	char statusmsg[80];
	time_t statusmsg_time;
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

void editorDelRow(int);
void editorFreeRow(erow*);
void editorInsertRow(int, char*, size_t);
void editorRowAppendString(erow*, char*, size_t);
int editorRowCxToRx(erow*, int);
int editorRowRxToCx(erow*, int);
void editorRowDelChar(erow *, int);
void editorRowInsertChar(erow*, int, int);
void editorUpdateRow(erow*);

/*** editor ops ***/

void editorDelChar();
void editorInsertChar(int);
void editorInsertNewline();

/*** file i/o ***/

void editorOpen(char*);
void editorSave();
char *editorRowsToString(int*);

/*** find ***/

void editorFind();
void editorFindCallback(char*, int);

/*** output ***/

void editorClearScreen(struct abuf*);
void editorDrawRows(struct abuf*);
void editorDrawMessageBar(struct abuf*);
void editorDrawStatusBar(struct abuf*);
void editorRefreshScreen();
void editorScroll();
void editorSetStatusMessage(const char*, ...);

/*** input ***/

void editorMoveCursor(int);
void editorProcessKeypress();
char *editorPrompt(char*, void (*)(char*, int));

/*** init ***/

void initEditor();

#endif
