#ifndef MEMORY
#define MEMORY

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct mmap mmap;
struct mmap {
  void* begin_addr;
  size_t size;
  bool available;
  mmap* next;
};

void init(uint32_t* multiboot);

#endif
