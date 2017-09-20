
#ifndef mix_columns_h
#define mix_columns_h

#include <stdio.h>
#include "aes-constants.h"

void mix_columns(byte state[AES_STATE_SPAN][AES_STATE_SPAN]);

#endif /* mix_columns_h */
