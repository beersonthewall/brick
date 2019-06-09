#include "memory.h"
#include "multiboot.h"
#include "terminal.h"
#include <stdbool.h>

#define FRAMES
#define FRAME_SIZE

char* mm_bitmap;
size_t mm_bitmap_size;

// PHYSICAL MEMORY FUNCTIONS

void pfree(void* paddr){
  // TODO
}

void* palloc(){
  // TODO
  return 0x00;
}

void debug(const char* msg, char typ, long val){
    terminal_writestring(msg);
    print(typ, val);
    write_newline();
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

  debug("Entries: ", 'l', entries);

  map_entry* entry = mem_map->entries;
  for(long i = 0; i < entries; i++) {

    debug("addr: ", 'd', entry->base);
    debug("len: ", 'd', entry->length);
    debug("type: ", 'd', entry->type);

    // Type of 1 == free, any other value is used in some way.
    if(entry->type == 1){
      long end_addr = (long) entry->base + entry->length;
      for(long addr = (long) entry->base; addr < end_addr; addr += FOUR_KB){
        mm_bitmap[(addr / FOUR_KB) / 8] |=
          1 << ((8 - ((addr / FOUR_KB) % 8)) - 1);
      }
    }
    entry = &mem_map->entries[i];
  }

  // TODO mark kernel and bitmap as used memory.

  terminal_writestring("\nDone mapping memory regions.");
}
