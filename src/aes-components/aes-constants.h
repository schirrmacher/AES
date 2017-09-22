
#include <stdint.h>

#ifndef aes_constants_h
#define aes_constants_h

typedef uint8_t byte;
typedef uint32_t word;

#define AES_256_ROUNDS 14
#define AES_256_KEY_WORDS 8
#define AES_ROUND_KEY_WORDS 4

#define AES_WORD_BYTES 4
#define AES_PLAINTEXT_WORDS 4
#define AES_CIPHERTEXT_WORDS 4
#define AES_STATE_SPAN 4

#define AES_IRREDUCIBLE_POLYNOMIAL 0x11b

#endif /* aes_constants_h */
