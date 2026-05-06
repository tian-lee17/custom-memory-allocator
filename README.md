# Custom Memory Allocator in C

## Overview
This project implements a custom memory allocator in C, replicating core behavior of `malloc` and `free`.

It demonstrates low-level memory management using a linked-list based allocator with block splitting and coalescing.

---

## Features
- Custom `my_malloc()` implementation
- Custom `my_free()` implementation
- Block splitting to avoid memory waste
- Coalescing (merging) of free blocks
- Memory block visualization (`print_blocks`)

---

## How it Works
- A large memory pool is created using `malloc`
- Each block contains metadata:
  - size
  - free/allocated status
  - pointer to next block
- Memory is allocated using a **first-fit strategy**
- Free blocks are reused when possible
- Adjacent free blocks are merged to reduce fragmentation

---

## Example
Before allocation:
[Free Block]

After allocations:
[Used]-->[Used]-->[Free]


After freeing and coalescing:
[Free Block]

---

## How to Run

Compile:

gcc main.c -o allocator


Run:

./allocator


---

##Sample Output

Initial State:
Block 1 -> Size: 1000 | Free: 1

After allocating 200 bytes:
Block 1 -> Size: 200 | Free: 0
Block 2 -> Size: 784 | Free: 1

After freeing and coalescing:
Block 1 -> Size: 1000 | Free: 1


## Learning Outcome
- Understanding how `malloc` and `free` work internally
- Pointer arithmetic and memory layout
- Handling fragmentation in memory allocation


## Future Improvements
- Memory alignment support
- Best-fit allocation strategy
- Performance benchmarking
- Thread safety
