#include "savesheet.h"
#include "curses.h"

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



	//Make the status box
	
	StatusBox* statusbox = malloc(sizeof(AttributesBox));
	statusbox->maxHP = 10;
	statusbox->currentHP = 10;
	statusbox->bonusHP = 0;
	statusbox->hitdie = 8;
	statusbox->numhitdice = 1;
	statusbox->AC = 15;
	statusbox->initiative=0;
	
	newsheet->attributesbox = attributesbox;
	newsheet->characterbox = characterbox;
	newsheet->weaponsbox = weaponsbox;
	newsheet->statusbox = statusbox;

	return newsheet;
};

void saveSheet(Sheet* s, char* filename){
	FILE *f;
	f=fopen(filename, "w");
	CharacterBox* c = s->characterbox;
	fprintf(f,"%s,%s,%d,%d\n", c->name,c->classname,c->exp,c->gold);

	StatusBox* st = s->statusbox;
	fprintf(f,"%d,%d,%d,%d,%d,%d,%d\n",
	st->maxHP,
	st->currentHP,
	st->bonusHP,
	st->hitdie,
	st->numhitdice,
	st->AC,
	st->initiative);

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


	//Make the status box
	StatusBox* st = malloc(sizeof(StatusBox));
	fscanf(f,"%d,%d,%d,%d,%d,%d,%d\n",
	&st->maxHP,
	&st->currentHP,
	&st->bonusHP,
	&st->hitdie,
	&st->numhitdice,
	&st->AC,
	&st->initiative);


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
	newsheet->statusbox = st;
	newsheet->characterbox = characterbox;
	newsheet->weaponsbox = weaponsbox;

	fclose(f);
	return newsheet;
}

void saveSheetDiag(Sheet* sheet) {
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,20,my/2-2,mx/2-10);
	drawBorders(win);

	char filename[STR_SIZE];
	mvwprintw(win,1,1,"Save Sheet");
	mvwprintw(win,2,1,"Name: ");

	wrefresh(win);
	
	nocbreak();
	echo();
	wgetstr(win,filename);

	cbreak();
	noecho();

	werase(win);
	wrefresh(win);
	saveSheet(sheet, filename);

}
