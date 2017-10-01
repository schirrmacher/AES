
#include "./shift-rows.h"
#include <string.h>
#include <limits.h>


void shift_rows(state state) {
    
    byte result[AES_STATE_SPAN][AES_STATE_SPAN];
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            result[i][j] = state[i][(i + j) % AES_STATE_SPAN];
        }
    }
    
    memcpy(state, result, sizeof(byte) * AES_STATE_SPAN * AES_STATE_SPAN);
}
