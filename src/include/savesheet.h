#ifndef SAVESHEET
#define SAVESHEET

#include "sheet.h"
#include "options.h"

Sheet* makeDefaultSheet();
void saveSheet(Sheet*, char*);
void saveSheetDiag(Sheet*);
Sheet* openSheet(char*);



#endif
