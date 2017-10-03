
#include "./shift-rows.h"
#include <string.h>
#include <limits.h>


void shift_rows(state state_ref) {
    
    state result;
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            result[i][j] = state_ref[i][(j + i) % AES_STATE_SPAN];
        }
    }
    
    memcpy(state_ref, result, sizeof(byte) * AES_STATE_SPAN * AES_STATE_SPAN);
}

void inv_shift_rows(state state_ref) {
    
    state result;
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            result[i][j] = state_ref[i][(4 + j - i) % AES_STATE_SPAN];
        }
    }
    
    memcpy(state_ref, result, sizeof(byte) * AES_STATE_SPAN * AES_STATE_SPAN);
}
