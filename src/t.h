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

/*** macros ***/

#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/

struct editorConfig{
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

void editorClearScreen();
void editorDrawRows();
void editorRefreshScreen();

/*** input ***/

void editorProcessKeypress();

/*** init ***/

void initEditor();

#endif
