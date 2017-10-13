
#include "pkcs7.h"

/*
 
 RFC 5652
 
 the input shall be padded at the trailing end with
 k-(lth mod k) octets all having value k-(lth mod k), where lth is
 the length of the input
 
 This padding method is well defined if and only if k is less than 256.
 
 */

#define MAX_PADDING_BYTES 32

void pkcs7_padded_content_bytes(const size_t block_bytes, const size_t content_bytes, size_t *new_content_size) {
    *new_content_size = block_bytes - (content_bytes % block_bytes);
}

enum pkcs7_status pkcs7_pad(const size_t bytes_to_be_padded, uint8_t *content_to_be_padded, const size_t content_bytes) {
    
    if (MAX_PADDING_BYTES < bytes_to_be_padded) {
        return EXCEEDED_ALLOWED_PADDING_LENGTH;
    }
    
    unsigned long padding_offset = content_bytes - bytes_to_be_padded;
    unsigned long bytes_sum = content_bytes + bytes_to_be_padded;
    
    for (unsigned long i = padding_offset; i < bytes_sum; i++) {
        content_to_be_padded[i] = bytes_to_be_padded;
    }
    
    return OK;
}

void pkcs7_unpadded_content_bytes(uint8_t *padded_content, const size_t content_bytes, size_t *new_content_bytes) {
    // last byte reveals how many bytes where padded
    unsigned long padded_bytes = padded_content[content_bytes - 1];
    *new_content_bytes = content_bytes - padded_bytes;
}
