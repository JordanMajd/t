#ifndef T_H
#define T_H

/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** macros ***/

#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/

struct editorConfig{
	struct termios orig_termios;
};

struct editorConfig E;

/*** terminal ***/

void die(const char*);
void disableRawMode();
void enableRawMode();
char editorReadKey();

/*** output ***/

void editorClearScreen();
void editorDrawRows();
void editorRefreshScreen();

/*** input ***/

void editorProcessKeypress();

#endif
