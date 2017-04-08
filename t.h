#ifndef T_H
#define T_H

#define CTRL_KEY(k) ((k) & 0x1f)

/*** terminal ***/

void die(const char*);
void disableRawMode();
void enableRawMode();
char editorReadKey();

/*** output ***/

void editorRefreshScreen();
void editorClearScreen();

/*** input ***/

void editorProcessKeypress();


#endif
