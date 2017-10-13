
#ifndef pkcs7_h
#define pkcs7_h

#include <stdio.h>

enum pkcs7_status {
    OK = 0,
    EXCEEDED_ALLOWED_PADDING_LENGTH,
    ARRAY_SHORTER_THAN_PADDING
};

void pkcs7_padded_content_bytes(const size_t block_bytes, const size_t content_bytes, size_t *new_content_size);

enum pkcs7_status pkcs7_pad(const size_t bytes_to_be_padded, uint8_t *content_to_be_padded, const size_t content_bytes);

void pkcs7_unpadded_content_bytes(uint8_t *padded_content, const size_t content_bytes, size_t *new_content_bytes);

#endif /* pkcs7_h */
