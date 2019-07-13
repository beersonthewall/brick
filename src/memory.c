#include "memory.h"
#include "multiboot.h"
#include "terminal.h"
#include <stdbool.h>

#define FRAMES
#define FRAME_SIZE

char* mm_bitmap;
size_t mm_bitmap_size;

// start and end of the kernel.
extern void _start;
extern void _end;

void debug(const char* msg, char typ, long val){
    terminal_writestring(msg);
    print(typ, val);
    write_newline();
}

void unmark(void* phys_addr, size_t sz) {
  uint64_t end = (uint64_t) phys_addr + sz;
  for(uint64_t i = (uint64_t) phys_addr; i <= end; i+= FOUR_KB){
    mm_bitmap[PAGE_NO(i)] &= ~ (1 << ((8 - ((i / FOUR_KB) % 8)) - 1));
  }
}

void mark(void* phys_addr, size_t sz){
  uint64_t end = (uint64_t) phys_addr + sz;
  for(uint64_t i = (uint64_t) phys_addr; i <= end; i+= FOUR_KB){
    mm_bitmap[PAGE_NO(i)] |= (8 - ((i / FOUR_KB) % 8)) - 1;
  }
}

/*
 * Physical memory initialization.
 */
void mm_init(uint32_t* multiboot) {
  memory_map* mem_map = (memory_map*) get_tag(MEM_MAP, multiboot);
  basic_mem_info* info = (basic_mem_info*) get_tag(BASIC_MEM_INFO, multiboot);
  long entries = (mem_map->size - 4*sizeof(uint32_t)) / mem_map->entry_sz;

  // # pages / 8
  mm_bitmap_size = (((info->mem_upper / ONE_KB) + 1) * 256) / 8;
  // Address of the mutliboot struct + it's size. Avoids overwriting it.
  mm_bitmap = (void*) multiboot + ((uint32_t) *multiboot);

  // Initially mark all pages as used.
  size_t size = mm_bitmap_size;
  char* map = mm_bitmap;
  while(size--){
    *map++ = 0xFF;
  }

  map_entry* entry = mem_map->entries;
  for(long i = 0; i < entries; i++) {

    // Type of 1 == free, any other value is used in some way.
    if(entry->type == 1){
      uint64_t end_addr = (uint64_t) entry->base + entry->length;
      for(uint64_t addr = (uint64_t) entry->base; addr < end_addr; addr += FOUR_KB){
        mm_bitmap[PAGE_NO(addr)] &=
          ~ (1 << ((8 - ((addr / FOUR_KB) % 8)) - 1));
      }
    }
    entry = &mem_map->entries[i];
  }

  // Mark the kernel, multiboot struct, and the bitmap itself
  // as used.
  uint64_t end_used =
    (uint64_t) &_end + ((uint64_t) mm_bitmap + mm_bitmap_size);
  for(uint64_t addr = (uint64_t) &_start; addr <= end_used; addr+=FOUR_KB){
    mm_bitmap[PAGE_NO(addr)] |= (8 - ((addr / FOUR_KB) % 8)) - 1;
  }
  terminal_writestring("Done marking physical pages as used.");
}
