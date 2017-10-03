
#include <assert.h>
#include <inttypes.h>
#include "./aes-components/aes.h"


static void test_equality(block expected, block actual);
static void print_block(block block);

int main(int argc, const char * argv[]) {
    
    key key = {
        0x603deb10, 0x15ca71be, 0x2b73aef0, 0x857d7781, 0x1f352c07, 0x3b6108d7, 0x2d9810a3, 0x0914dff4
    };
    
    block plaintext = {
        0xae2d8a57, 0x1e03ac9c, 0x9eb76fac, 0x45af8e51
    };
    
    block ciphertext = {
        0x591ccb10, 0xd410ed26, 0xdc5ba74a, 0x31362870
    };
    
    printf("Encryption Test:");
    block encryption_result;
    //aes_256_encrypt_block(key, plaintext, encryption_result);
    //test_equality(ciphertext, encryption_result);
    
    printf("Decryption Test:");
    block decryption_result;
    aes_256_decrypt_block(key, ciphertext, decryption_result);
    test_equality(plaintext, decryption_result);
    
    return 0;
}

static void test_equality(block expected, block actual) {
    printf("\n   ");
    print_block(expected);
    printf("\n== ");
    print_block(actual);
    for (int i = 0; i < 4; i++) {
        if (actual[i] != expected[i]) {
            printf("❌\n\n");
        }
        assert(actual[i] == expected[i]);
    }
    printf("✅\n\n");
}

static void print_block(block block) {
    for (int i = 0; i < 4; i++) {
        printf("%08" PRIx32 " ", block[i]);
    }
}
