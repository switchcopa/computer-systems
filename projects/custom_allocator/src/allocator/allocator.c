#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"

static unsigned char allocbuf[HEAP_SIZE]; // This is the "heap",
                                        // even though it's stored in initialized memory.
static struct mem_block *head_block = NULL;

// Run this before main, compile with GCC
__attribute__((constructor))
static void auto_init_allocator(void) {
    init_allocator();
}

void init_allocator(void) {
    head_block = (struct mem_block *)allocbuf; // make the first sizeof(struct mem_block *) bytes of allocbuf
                                            // those those of head_block

    head_block->next_block = NULL;
    head_block->free = 1;
    head_block->block_size = HEAP_SIZE - sizeof(struct mem_block *);
}

// If the requested size is enough, we create another block_size
// and return only the requested
static void split_block(struct mem_block *block, size_t size) {
    if (block->block_size >= size + sizeof(struct mem_block) + 1) {
        struct mem_block *new_block = (struct mem_block *)((unsigned char *)block + size + sizeof(struct mem_block) + size);
        
        new_block->block_size = block->block_size - size - sizeof(struct mem_block);
        new_block->free = 1;
        new_block->next_block = block->next_block;

        block->block_size = size;
        block->next_block = new_block;
    }
}

// Call this before freeing to reduce block fragmentation
// This memory pools large allocations
static void coalesce_block(void)
{
    struct mem_block *curr = head_block; 

    while (curr && curr->next_block) {
        if (curr->free && curr->next_block->free) {
            curr->block_size += sizeof(struct mem_block) + curr->next_block->block_size;
            curr->next_block = curr->next_block->next_block;
        } else {
            curr = curr->next_block;
        }
    }
}

void *zalloc(size_t size)
{
    if (!head_block)
        init_allocator();

    struct mem_block *curr = head_block;
    while (curr) {
        if (curr->free && curr->block_size >= size) {
            split_block(curr, size);
            curr->free = 0;
            return (void*)((unsigned char *)curr + sizeof(struct mem_block));
        }
    }

    return NULL;
}

void zfree(void *ptr) {
    if (!ptr)
        return;

    struct mem_block *block = (void*)((unsigned char *)ptr - sizeof(struct mem_block));
    block->free = 1;
    coalesce_block();
}
