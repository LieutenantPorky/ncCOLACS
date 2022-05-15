#include "main.h"


SelectionState* state;

int main(int argc, char * argv[]) {

	Sheet* sheet;
	if (argc > 1) {
		sheet = openSheet("test.char");
	} else {
		sheet = makeDefaultSheet();
	}

	if (!DEBUG) {
		init();
		populateWindows(sheet);
	}

	state = malloc(sizeof(SelectionState));
	state->SelectedBox = ATTRIBUTES;
	state->SelectedItem = 0;




	drawSheet(sheet);
	//saveSheet(sheet, "test1.char");
	if (DEBUG) {return 1;}

	while (true) {
	}



}

// Init and finish functions
static void init() {
	(void) signal(SIGINT, finish);      /* arrange interrupts to terminate */

	(void) initscr();      /* initialize the curses library */
	keypad(stdscr, TRUE);  /* enable keyboard mapping */
	(void) nonl();         /* tell curses not to do NL->CR/NL on output */
	(void) cbreak();       /* take input chars one at a time, no wait for \n */
	(void) echo();         /* echo input - in color */

	if (has_colors())
	{
		start_color();
	}
	(void) curs_set(0);
}

static void finish(int sig) {
	endwin();
	int MAIN_X;
	int MAIN_Y;
	//printf("X: %d, Y: %d\n", MAIN_X,MAIN_Y);
	exit(0);
};

