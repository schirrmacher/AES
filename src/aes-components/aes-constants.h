
#include <stdint.h>

#ifndef aes_constants_h
#define aes_constants_h

typedef uint32_t block[4];
typedef uint8_t byte;

#define AES_256_ROUNDS 14

#define AES_256_KEY_WORDS 8
typedef uint32_t key[AES_256_KEY_WORDS];

#define AES_WORD_BYTES 4
typedef byte word[AES_WORD_BYTES];

#define AES_STATE_SPAN 4
typedef byte state[AES_STATE_SPAN][AES_STATE_SPAN];
typedef byte round_key[AES_STATE_SPAN][AES_STATE_SPAN];

#define AES_IRREDUCIBLE_POLYNOMIAL 0x11b

#endif /* aes_constants_h */
