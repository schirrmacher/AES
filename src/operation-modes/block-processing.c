
#include "block-processing.h"
#include <stdlib.h>


void process_blocks(uint8_t *all_blocks,
                    const size_t all_blocks_bytes,
                    const size_t single_block_bytes,
                    void (^process_block)(uint8_t *block, unsigned long index))
{
    
    if (all_blocks_bytes % single_block_bytes != 0) {
        fprintf(stderr,
                "\nThe given plaintext with size %zu \
                can't be split into blocks of size %zu.\n",
                all_blocks_bytes,
                single_block_bytes);
        exit(EXIT_FAILURE);
    }
    
    const size_t all_blocks_count = all_blocks_bytes / single_block_bytes;
    
    for (unsigned long i = 0; i < all_blocks_count; i++) {
        
        uint8_t *current_block = all_blocks + (single_block_bytes * i);
        process_block(current_block, i);
        
    }
    
}
