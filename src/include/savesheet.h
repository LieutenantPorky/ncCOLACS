#ifndef SAVESHEET
#define SAVESHEET

#include "sheet.h"

Sheet* makeDefaultSheet();
void saveSheet(Sheet*, char*);
Sheet* openSheet(char*);



#endif
