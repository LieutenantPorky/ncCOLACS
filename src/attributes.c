#include "sheet.h"
#include "selectionstate.h"

void drawAttributesBox(AttributesBox * a){
	if (DEBUG){
		for (int i =0; i<NUM_ATTRIBUTES; i++){
			printf("%s: %d%c\n",ATTRIBUTE_NAMES[i], a->attributevalues[i], (a->proficiencies[i])? '*' : ' ');
		}
		return;
	}
	drawBorders(a->w);
	WINDOW* window = a->w;

	for(int i = 0; i<NUM_ATTRIBUTES;i++){
		int y = 1 + i*4;
		mvwprintw(window,y,1,"-------");
		wattron(window,A_BOLD);
		if (state->SelectedBox == ATTRIBUTES && state->SelectedItem == i) {wattron(window, A_BLINK);}
		char * flag = (char*) a->proficiencies[i] ? "*" : " ";
		mvwprintw(window,y+1,1,"%s%s    ",flag,ATTRIBUTE_NAMES[i]);
		wattroff(window,A_BOLD);
		mvwprintw(window,y+2,1," %d(%+d) ", a->attributevalues[i], getBonus(a->attributevalues[i]));
		if (state->SelectedBox == ATTRIBUTES && state->SelectedItem == i) {wattroff(window, A_BLINK);}
		mvwprintw(window,y+3,1,"-------");



	}

	wrefresh(a->w);
}
