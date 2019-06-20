#ifndef MEMORY
#define MEMORY

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define ONE_KB 1024
#define FOUR_KB 4096

void pfree(void* paddr);

void* palloc(size_t size);

void mm_init(uint32_t* multiboot);

#endif
