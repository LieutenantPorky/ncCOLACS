#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "options.h"
#include "sheet.h"

extern SelectionState* state;

static void init();
static void finish(int);
