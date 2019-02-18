#ifndef MEMORY
#define MEMORY

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define ONE_KB 1024


typedef struct mmap mmap;
struct mmap {
  void* begin_addr;
  size_t size;
  bool available;
  mmap* next;
};

void mm_init(uint32_t* multiboot);

#endif
