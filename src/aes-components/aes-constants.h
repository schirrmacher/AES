
#include <stdint.h>

#ifndef aes_constants_h
#define aes_constants_h


#define AES_256_ROUNDS 14

typedef uint8_t byte;

#define AES_BLOCK_BYTES 16
typedef byte block[AES_BLOCK_BYTES];

#define AES_256_KEY_BYTES 32
typedef byte key[AES_256_KEY_BYTES];

#define AES_WORD_BYTES 4
typedef byte word[AES_WORD_BYTES];

#define AES_STATE_SPAN 4
typedef byte state[AES_STATE_SPAN][AES_STATE_SPAN];
typedef byte round_key[AES_STATE_SPAN][AES_STATE_SPAN];

#define AES_IRREDUCIBLE_POLYNOMIAL 0x11b

#endif /* aes_constants_h */
