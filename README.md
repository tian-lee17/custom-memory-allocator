# Custom Memory Allocator in C

## Overview
This project is a simple implementation of a custom memory allocator, similar to `malloc` and `free`, written in C.

It demonstrates how memory is managed internally using a linked list of memory blocks.

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

## Learning Outcome
- Understanding how `malloc` and `free` work internally
- Pointer arithmetic and memory layout
- Handling fragmentation in memory allocation
