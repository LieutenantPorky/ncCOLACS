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

	state = getNewState();

	drawSheet(sheet);
	//saveSheet(sheet, "test1.char");
	if (DEBUG) {return 1;}

	while (true) {
		processInput(sheet,state);
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
	exit(0);
};

