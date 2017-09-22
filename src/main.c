
#include <assert.h>
#include "./aes-components/aes.h"


static void print_state(byte state[AES_STATE_SPAN][AES_STATE_SPAN]);

int main(int argc, const char * argv[]) {
    
    word key[AES_256_KEY_WORDS] = {
        0x603deb10, 0x15ca71be, 0x2b73aef0, 0x857d7781, 0x1f352c07, 0x3b6108d7, 0x2d9810a3, 0x0914dff4
    };
    
    word plaintext[AES_PLAINTEXT_WORDS] = {
        0xae2d8a57, 0x1e03ac9c, 0x9eb76fac, 0x45af8e51
    };
    
    word expected[AES_CIPHERTEXT_WORDS] = {
        0x591ccb10, 0xd410ed26, 0xdc5ba74a, 0x31362870
    };
    
    byte result[AES_STATE_SPAN][AES_STATE_SPAN];
    aes_256_encrypt_block(plaintext, key, result);
    
    byte expected_bytes[AES_STATE_SPAN][AES_STATE_SPAN];
    for (int i = 0; i < AES_CIPHERTEXT_WORDS; i++) {
        expected_bytes[0][i] = (expected[i] >> 24) & 0xFF;
        expected_bytes[1][i] = (expected[i] >> 16) & 0xFF;
        expected_bytes[2][i] = (expected[i] >>  8) & 0xFF;
        expected_bytes[3][i] =  expected[i]        & 0xFF;
    }
    
    printf("Expected:");
    print_state(expected_bytes);
    
    printf("Actual:");
    print_state(result);
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (result[i][j] != expected_bytes[i][j]) {
                printf("❌ Test failed.\n\n");
            }
            assert(result[i][j] == expected_bytes[i][j]);
        }
    }
    
    printf("✅ Test succeeded!\n\n");
    
    return 0;
}

static void print_state(byte state[4][4]) {
    printf("\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            const byte current_value = state[i][j];
            printf("%02hhX ", current_value);
        }
        printf("\n");
    }
    printf("\n");
}
