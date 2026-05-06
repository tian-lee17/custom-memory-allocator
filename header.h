#include <stdio.h>
#include <stdlib.h>

#define MEM_BLK 1000   // Total memory pool size

#define FAILURE -1
#define SUCCESS 0

// Metadata structure representing a memory block
typedef struct block
{
    int size;           // Size of usable memory in this block
    int free;           // 1 = free, 0 = allocated
    struct block *next; // Pointer to next block in the list
} block;

// Allocates memory using custom allocator
void *my_malloc(int size);

// Frees allocated memory block
void my_free(void *ptr);

// Merges adjacent free blocks to reduce fragmentation
void coalesce();

// Prints current state of memory blocks (for debugging/visualization)
void print_blocks();