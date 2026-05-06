#include "header.h"

block *head;  // Global pointer to the start of the memory block list

int main()
{
    // Allocate a large contiguous memory pool
    printf("Total Memory Pool: %d bytes\n", MEM_BLK);
    void *memory = malloc(MEM_BLK);
    if (memory == NULL)
    {
        perror("malloc");
        return FAILURE;
    }

    // Initialize the first block metadata at the start of the pool
    head = (block *)memory;
    head->size = MEM_BLK - sizeof(block);
    head->free = 1;
    head->next = NULL;

    printf("\n===== CUSTOM MEMORY ALLOCATOR DEMO =====\n");

    print_blocks();  // Display initial state

    // -------------------------------
    printf("\n[1] Allocating p1 (200 bytes)\n");
    void *p1 = my_malloc(200);
    printf("p1: %p\n", p1);
    print_blocks();  // Shows block splitting

    // -------------------------------
    printf("\n[2] Allocating p2 (100 bytes)\n");
    void *p2 = my_malloc(100);
    printf("p2: %p\n", p2);
    print_blocks();  // Further splitting

    // -------------------------------
    printf("\n[3] Freeing p1 (testing reuse)\n");
    my_free(p1);
    print_blocks();  // p1 becomes free

    printf("\nAllocating p3 (200 bytes) — should reuse p1\n");
    void *p3 = my_malloc(200);
    printf("p3: %p\n", p3);
    print_blocks();  // Should reuse same block as p1

    // -------------------------------
    printf("\n[4] Freeing p2 and p3 (testing coalescing)\n");
    my_free(p2);
    my_free(p3);
    print_blocks();  // Adjacent free blocks should merge

    // -------------------------------
    printf("\n[5] Allocating p4 (300 bytes) — requires coalescing\n");
    void *p4 = my_malloc(300);
    printf("p4: %p\n", p4);
    print_blocks();  // Should succeed only if coalescing worked

    printf("\n===== DEMO COMPLETE =====\n");

    return 0;
}

// Allocates memory using first-fit strategy with optional block splitting
void *my_malloc(int size)
{
    block *temp = head;

    // Traverse the block list to find a suitable free block
    while (temp != NULL)
    {
        // Check if current block is free and large enough
        if (temp->free == 1 && temp->size >= size)
        {
            // Check if splitting is possible (enough space for new metadata)
            if (temp->size - size > sizeof(block))
            {
                // Move pointer to the location where new block will start
                char *ptr = (char *)(temp + 1);
                ptr = ptr + size;

                // Create new block from remaining memory
                block *new = (block *)ptr;

                // Assign remaining size after splitting (including metadata adjustment)
                new->size = temp->size - size - sizeof(block);
                new->free = 1;
                new->next = temp->next;

                // Update current block to reflect allocated size
                temp->size = size;
                temp->next = new;
            }

            // Mark current block as allocated
            temp->free = 0;

            // Return pointer to usable memory (after metadata)
            return (void *)(temp + 1);
        }

        temp = temp->next;  // Move to next block
    }

    return NULL;  // No suitable block found
}

// Frees allocated memory and triggers coalescing to reduce fragmentation
void my_free(void *ptr)
{
    if (ptr == NULL)
        return;

    // Move back to metadata from user pointer
    block *p = (block *)ptr - 1;

    p->free = 1;  // Mark block as free

    coalesce();   // Merge adjacent free blocks if possible
}

// Merges consecutive free blocks into a single larger block
void coalesce()
{
    block *temp = head;

    // Traverse and merge adjacent free blocks
    while (temp != NULL && temp->next != NULL)
    {
        // If both current and next blocks are free, merge them
        if (temp->free == 1 && temp->next->free == 1)
        {
            // Increase size by including next block and its metadata
            temp->size += temp->next->size + sizeof(block);

            // Remove next block from list
            temp->next = temp->next->next;
        }
        else
        {
            temp = temp->next;  // Move forward only if no merge
        }
    }
}

// Prints the current state of all memory blocks for visualization
void print_blocks()
{
    block *temp = head;
    int i = 1;

    printf("\n--- Memory Blocks ---\n");

    while (temp != NULL)
    {
        printf("Block %d -> Addr: %p | Size: %d | Free: %d | Next: %p\n",
               i, temp, temp->size, temp->free, temp->next);

        temp = temp->next;
        i++;
    }

    printf("----------------------\n");
}