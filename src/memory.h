#ifndef MEMORY
#define MEMORY

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define ONE_KB 1024
#define FOUR_KB 4096

#define PAGE_NO(addr) (size_t) ((addr / FOUR_KB) / 8)


void unmark(void*, size_t);

void mark(void*, size_t);

void mm_init(uint32_t* multiboot);

#endif
