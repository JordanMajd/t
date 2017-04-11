#ifndef T_H
#define T_H

/*** includes ***/

#include "abuf.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/*** macros & defs ***/

#define CTRL_KEY(k) ((k) & 0x1f)
#define T_VERSION "0.0.1"

/*** data ***/

enum editorKey{
	ARROW_LEFT = 'h',
	ARROW_RIGHT = 'l',
	ARROW_UP = 'k',
	ARROW_DOWN = 'j'
};

struct editorConfig{
	int cx;
	int cy;
	int screenrows;
	int screencols;
	struct termios orig_termios;
};

struct editorConfig E;

/*** terminal ***/

void die(const char*);
void disableRawMode();
char editorReadKey();
void enableRawMode();
int getCursorPosition(int*, int*);
int getWindowSize(int*, int*);

/*** output ***/

void editorClearScreen(struct abuf*);
void editorDrawRows(struct abuf*);
void editorRefreshScreen();

/*** input ***/

void editorMoveCursor(char);
void editorProcessKeypress();

/*** init ***/

void initEditor();

#endif
