
#ifndef substitute_h
#define substitute_h

#include <stdio.h>
#include "aes-constants.h"

extern byte substitutes[256];

void substitute(state state);

#endif /* substitute_h */
