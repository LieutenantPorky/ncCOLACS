#include "sheet.h"


Sheet * makeDefaultSheet(){
	Sheet* newsheet = malloc(sizeof(Sheet));

	// Make the character box
	CharacterBox* characterbox = malloc(sizeof(CharacterBox));
	strcpy(characterbox->name,"Bilbo Baggins");
	strcpy(characterbox->classname,"Hobbit pipeweed smoker");
	characterbox->exp = 0;
	characterbox->gold = 0;

	// Make the weapon box
	Weapon* testweapon = malloc(sizeof(Weapon));
	strcpy(testweapon->name,"Walloping Stick");
	testweapon->attr = 0;
	testweapon->numdice=1;
	testweapon->die=4;

	WeaponsBox* weaponsbox = malloc(sizeof(WeaponsBox));
	weaponsbox->numweapons=0;
	addWeapon(weaponsbox,testweapon);
	weaponsbox->selected=0;

	//Make the attributes box

	AttributesBox* attributesbox = malloc(sizeof(AttributesBox));
	static const int def_att[] = {10,10,10,10,10,10};
	static const bool def_prof[] = {false,true,false,false,true,false};
	memcpy(attributesbox->attributevalues,def_att,sizeof(def_att));
	memcpy(attributesbox->proficiencies,def_prof,sizeof(def_prof));

	newsheet->attributesbox = attributesbox;
	newsheet->characterbox = characterbox;
	newsheet->weaponsbox = weaponsbox;

	return newsheet;
};


void addWeapon(WeaponsBox* wb, Weapon* w){
	// add a new weapon to the weaponsbox
	wb->numweapons++;
	wb->weapons = realloc(wb->weapons, wb->numweapons * sizeof(Weapon));
	wb->weapons[wb->numweapons - 1]= *w;
}



void saveSheet(Sheet* s, char* filename){
	FILE *f;
	f=fopen(filename, "w");
	CharacterBox* c = s->characterbox;
	fprintf(f,"%s,%s,%d,%d\n", c->name,c->classname,c->exp,c->gold);

	AttributesBox* a = s->attributesbox;
	for (int i =0; i<NUM_ATTRIBUTES; i++){
		fprintf(f,"%d,",a->attributevalues[i]);
	}
	fprintf(f,"\n");
	for (int i =0; i<NUM_ATTRIBUTES; i++){
		fprintf(f,"%d,",a->proficiencies[i]);
	}
	fprintf(f,"\n");

	WeaponsBox* w = s->weaponsbox;
	Weapon *cw;
	fprintf(f,"%d\n",w->numweapons);
	for(int i=0;i<w->numweapons;i++) {
		cw=&w->weapons[i];
		fprintf(f,"%s,%d,%d,%d\n",cw->name,cw->numdice,cw->die,a->attributevalues[cw->attr]);
	}

	fclose(f);
}

Sheet* openSheet(char* filename) {
	Sheet* newsheet = malloc(sizeof(Sheet));
	FILE* f;
	f = fopen(filename,"r");

	// Make the character box
	CharacterBox* characterbox = malloc(sizeof(CharacterBox));
	char name[STR_SIZE]; char classname[STR_SIZE]; int exp; int gold;
	fscanf(f,"%64[^,],%64[^,],%d,%d\n",&name[0],&classname[0],&exp,&gold);



	strcpy(characterbox->name,name);
	strcpy(characterbox->classname,classname);
	characterbox->exp = exp;
	characterbox->gold = gold;

	//Make the attributes box

	AttributesBox* attributesbox = malloc(sizeof(AttributesBox));
	int def_att[NUM_ATTRIBUTES];
	int def_prof[NUM_ATTRIBUTES];

	fscanf(f,"%d,%d,%d,%d,%d,%d,\n",
		&def_att[0],
		&def_att[1],
		&def_att[2],
		&def_att[3],
		&def_att[4],
		&def_att[5]
		);

	fscanf(f,"%d,%d,%d,%d,%d,%d,\n",
		&def_prof[0],
		&def_prof[1],
		&def_prof[2],
		&def_prof[3],
		&def_prof[4],
		&def_prof[5]
		);

	bool def_prof_b[NUM_ATTRIBUTES];
	for (int i = 0; i<NUM_ATTRIBUTES;i++) {def_prof_b[i] = def_prof[i];}

	memcpy(attributesbox->attributevalues,def_att,sizeof(def_att));
	memcpy(attributesbox->proficiencies,def_prof_b,sizeof(def_prof_b));

	// Make the weapon box
	int numweapons;
	fscanf(f,"%d\n",&numweapons);

	WeaponsBox* weaponsbox = malloc(sizeof(WeaponsBox));
	weaponsbox->numweapons=0;

	for(int i = 0; i<numweapons; i++){
		Weapon* testweapon = malloc(sizeof(Weapon));
		char name[STR_SIZE];
		int attr;
		int numdice;
		int die;

		//fgets(name,STR_SIZE,f);
		//printf("string: %s\n",name);

		fscanf(f,"%64[^,],%d,%d,%d\n",&name[0],&numdice,&die,&attr);
		strcpy(testweapon->name,name);
		testweapon->attr = attr;
		testweapon->numdice=numdice;
		testweapon->die=die;
		addWeapon(weaponsbox,testweapon);
	}

	weaponsbox->selected=0;


	newsheet->attributesbox = attributesbox;
	newsheet->characterbox = characterbox;
	newsheet->weaponsbox = weaponsbox;

	fclose(f);
	return newsheet;
}

// graphics part
void drawBorders(WINDOW * screen) {
	int x;
	int y;
	getmaxyx(screen, y,x);
	for (int i = 0; i<y; i++) {mvwaddch(screen, i, 0, '|');}
	for (int i = 0; i<y; i++) {mvwaddch(screen, i, x-1, '|');}
	for (int i = 0; i<x; i++) {mvwaddch(screen, 0, i, '-');}
	for (int i = 0; i<x; i++) {mvwaddch(screen, y-1, i, '-');}

	mvwaddch(screen, 0, 0, '+');
	mvwaddch(screen, y-1, 0, '+');
	mvwaddch(screen, 0, x-1, '+');
	mvwaddch(screen, y-1, x-1, '+');
}

void populateWindows(Sheet* s) {
	int MAIN_X;
	int MAIN_Y;
	getmaxyx(stdscr,MAIN_Y,MAIN_X);

	s->characterbox->w = newwin(4,MAIN_X,0,0);
	s->attributesbox->w = newwin(2+NUM_ATTRIBUTES*4,10,5,0);
	s->weaponsbox->w = newwin(2+ 2 * s->weaponsbox->numweapons,MAIN_X/2,5,11);
}

void drawSheet(Sheet* s){
	drawCharacterBox(s->characterbox);
	drawAttributesBox(s->attributesbox);
	drawWeaponsBox(s->weaponsbox,s);
}

void drawCharacterBox(CharacterBox* c){
	if (DEBUG){
		printf("name: %s, class: %s, exp: %d, gold: %d\n", c->name,c->classname,c->exp,c->gold);
		return;
	}
	drawBorders(c->w);
	int x;
	int y;
	WINDOW* window = c->w;
	getmaxyx(window, y,x);

	mvwprintw(window,1,1,"LVL %d %s", getLVL(c->exp), c->classname);

	wattron(window,A_BOLD);
	mvwprintw(window,2,1,"GOLD: ");
	wattroff(window,A_BOLD);
	wprintw(window,"%d",c->gold);

	int namelen = strlen(c->name);
	char buff[STR_SIZE];
	sprintf(buff,"LVL %d %s", getLVL(c->exp), c->classname);

	// choose if to align on center or right
	int namex;
	if (namelen/2 + strlen(buff) + 4 < x/2) {namex = x/2 - namelen/2;}
	else {namex = x - namelen - 1;}
	wattron(window,A_BOLD);
	mvwprintw(window,1,namex,"%s",c->name);
	wattroff(window,A_BOLD);

	wrefresh(c->w);
}

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

void drawWeaponsBox(WeaponsBox* w, Sheet* s) {
	if (DEBUG) {
		Weapon *cw;
		printf("numweapons: %d\n",w->numweapons);
		for(int i=0;i<w->numweapons;i++) {
			cw=&w->weapons[i];
			printf("%s: %dd%d+%d\n",cw->name,cw->numdice,cw->die,s->attributesbox->attributevalues[cw->attr]);
		}
		return;
	}
	drawBorders(w->w);
	WINDOW* window = w->w;

	int name_len = 1;
	for(int i =0; i<w->numweapons;i++){
		Weapon * wp = &(w->weapons[i]);
		int new_name_len = strlen(wp->name);
		if (new_name_len>name_len){name_len = new_name_len;}
	}

	for(int i =0; i<w->numweapons;i++){
		Weapon * wp = &(w->weapons[i]);
		mvwprintw(window,1+2*i,1,"%s",wp->name);


		wattron(window, A_BOLD);
		mvwprintw(window,1+2*i,name_len+2,"| %dD%d + %d |",wp->numdice,wp->die, 
			getProficiency(s->characterbox->exp) + getBonus(s->attributesbox->attributevalues[wp->attr]));
		//mvwprintw(window,1+2*i,20,"%s",w->attribute->title);
		wattroff(window,A_BOLD);
	}

	wrefresh(w->w);
}
