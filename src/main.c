
#include <assert.h>
#include "./aes-components/aes.h"


static void print_state(byte state[4][4]);
static void print_hex_uint8(byte value);

int main(int argc, const char * argv[]) {
    
    word key[4] = {
        0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c
    };
    
    word plaintext[4] = {
        0x6bc1bee2, 0x2e409f96, 0xe93d7e11, 0x7393172a
        //0x3243f6a8, 0x885a308d, 0x313198a2, 0xe0370734
    };
    
    word expected[4] = {
        0x3ad77bb4, 0x0d7a3660, 0xa89ecaf3, 0x2466ef97
    };
    
    byte result[4][4];
    aes_encrypt(plaintext, key, result);
    
    byte expected_bytes[4][4];
    for (int i = 0; i < 4; i++) {
        expected_bytes[0][i] = (expected[i] >> 24) & 0xFF;
        expected_bytes[1][i] = (expected[i] >> 16) & 0xFF;
        expected_bytes[2][i] = (expected[i] >>  8) & 0xFF;
        expected_bytes[3][i] =  expected[i]        & 0xFF;
    }
    
    print_state(result);
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(result[i][j] == expected_bytes[i][j]);
        }
    }
    
    printf("\n\n");
    printf("✅ Test succeeded!\n");
    printf("\n\n");
    
    return 0;
}

static void print_state(byte state[4][4]) {
    printf("\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            const byte current_value = state[i][j];
            print_hex_uint8(current_value);
        }
        printf("\n");
    }
    printf("\n");
}

static void print_hex_uint8(byte value) {
    printf("%02hhX ", value);
}
