
#ifndef aes_h
#define aes_h

#include <stdio.h>
#include "aes-constants.h"

void aes_256_encrypt_block(block plaintext, key input_key, block result_block_ref);

#endif /* aes_h */
