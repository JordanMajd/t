#include "t.h"

/*** terminal ***/

void die(const char *s){
	//clear screen, reset cursor
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	perror(s);
	exit(1);
}

void disableRawMode(){
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1){
		die("tcsetattr");
	}
}

char editorReadKey(){

	int nread;
	char c;

	while((nread = read(STDIN_FILENO, &c, 1)) != 1){
		if(nread == -1 && errno != EAGAIN){
			die("read");
		}
	}

	return c;
}

void enableRawMode(){

	if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1){
		die("tcgetattr");
	}

	atexit(disableRawMode);

	struct termios raw = E.orig_termios;

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP| IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1){
		die("tcsetattr");
	}
}

int getCursorPosition(int* rows, int* cols){
	
	char buf[32];
	unsigned int i = 0;

	if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4){
		return -1;
	}

	while(i < sizeof(buf) - 1){

		if(read(STDIN_FILENO, &buf[i], 1) != 1){
			break;
		}

		if(buf[i] == 'R'){
			break;
		}

		i++;
	}

	buf[i] = '\0';
	
	if(buf[0] != '\x1b' || buf[1] != '['){
		return -1;
	}

	if(sscanf(&buf[2], "%d;%d", rows, cols) != 2){
		return -1;
	}

	return 0;
}

int getWindowSize(int *rows, int *cols){
	struct winsize ws;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0){

		if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12){
			return -1;
		}

		return getCursorPosition(rows, cols);

	}else{
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return 0;
	}
}

/*** output ***/

void editorClearScreen(struct abuf *ab){
	abAppend(ab, "\x1b[2J", 4); //clear screen
	abAppend(ab, "\x1b[H", 3); //cursor top left
}

void editorDrawRows(struct abuf *ab){

	int y;
	for(y = 0; y < E.screenrows; y++){

		if(y == E.screenrows / 3){

			char welcome[80];
			int welcomelen = snprintf(welcome, sizeof(welcome), "T editor -- version %s", T_VERSION);

			if(welcomelen > E.screencols){
				welcomelen = E.screencols;
			}

			int padding = (E.screencols - welcomelen) / 2;
			if(padding){
				abAppend(ab, "~", 1);
				padding--;
			}
			while(padding--){
				abAppend(ab, " ", 1);
			}

			abAppend(ab, welcome, welcomelen);

		}else{

			abAppend(ab, "~", 1);
		}

		abAppend(ab, "\x1b[K", 3);//erase right of cursor

		if(y < E.screenrows - 1){
			abAppend(ab, "\r\n", 2);
		} 
	}
}

void editorRefreshScreen(){

	struct abuf ab = ABUF_INIT;

	abAppend(&ab, "\x1b[?25l", 6); //turn off cursor
	abAppend(&ab, "\x1b[H", 3); //cursor top left

	editorDrawRows(&ab);

	//move cursor to cy cx
	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);
	abAppend(&ab, buf, strlen(buf));

	abAppend(&ab, "\x1b[?25h", 6); //turn on cursor	

	write(STDOUT_FILENO, ab.b, ab.len);
	abFree(&ab);
}


/*** input ***/

void editorProcessKeypress(){

	char c = editorReadKey();

	switch(c){
		case CTRL_KEY('q'):
			//clear screen, cursor top left
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
			break;
	}
}

/*** init ***/

void initEditor(){

	E.cx = 0;
	E.cy = 0;

	if(getWindowSize(&E.screenrows, &E.screencols) == -1){
		die("getWindowSize");
	}
}

int main() {
	enableRawMode();
	initEditor();

	while(1){
		editorRefreshScreen();
		editorProcessKeypress();
	}

	return 0;
}

