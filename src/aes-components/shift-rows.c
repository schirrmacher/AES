
#include "./shift-rows.h"
#include <string.h>
#include <limits.h>


void shift_rows(uint32_t block[AES_STATE_MATRIX_SPAN]) {
    
    uint32_t result[AES_STATE_MATRIX_SPAN];
    
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        uint8_t bytes[4];
        bytes[0] = (block[i] >> 24) & 0xFF;
        bytes[1] = (block[i] >> 16) & 0xFF;
        bytes[2] = (block[i] >>  8) & 0xFF;
        bytes[3] =  block[i]        & 0xFF;
        result[i] =
            bytes[(0 + i) % AES_STATE_MATRIX_SPAN] << 24 |
            bytes[(1 + i) % AES_STATE_MATRIX_SPAN] << 16 |
            bytes[(2 + i) % AES_STATE_MATRIX_SPAN] <<  8 |
            bytes[(3 + i) % AES_STATE_MATRIX_SPAN];
    }
    
    memcpy(block, result, sizeof(result[0]) * AES_STATE_MATRIX_SPAN);
}
