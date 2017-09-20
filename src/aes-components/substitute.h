
#ifndef substitute_h
#define substitute_h

#include <stdio.h>
#include "aes-constants.h"

extern byte substitutes[256];

void substitute(byte state[AES_STATE_SPAN][AES_STATE_SPAN]);

#endif /* substitute_h */
