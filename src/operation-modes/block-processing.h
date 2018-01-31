
#ifndef block_processing_h
#define block_processing_h

#include <stdint.h>
#include <stdio.h>

void process_blocks(uint8_t *all_blocks,
                    const size_t all_blocks_bytes,
                    const size_t single_block_bytes,
                    void (^process_block)(uint8_t *block, unsigned long index));

#endif /* block_processing_h */
