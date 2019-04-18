#include "memory.h"
#include "multiboot.h"
#include "terminal.h"
#include <stdbool.h>

#define FRAMES
#define FRAME_SIZE

// Linker tag for end of the kernel. Placed immediately below the stack.
extern void _end;
extern void stack_top;

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

/*
 * Physical memory initialization.
 */
void mm_init(uint32_t* multiboot) {
  memory_map* mem_map = (memory_map*) get_tag(MEM_MAP, multiboot);
  basic_mem_info* info = (basic_mem_info*) get_tag(BASIC_MEM_INFO, multiboot);
  long entries = ((mem_map->size - 4) * sizeof(uint32_t)) / (mem_map->entry_sz);

  // # pages / 8
  mm_bitmap_size = (((info->mem_upper / ONE_KB) + 1) * 256) / 8;
  // Address of the mutliboot struct + it's size. Avoids overwriting it.
  mm_bitmap = (void*) multiboot + ((uint32_t) *multiboot);

  size_t size = mm_bitmap_size;
  char* map = mm_bitmap;
  while(size--){
    *map++ = 0x00;
  }
  terminal_writestring("Physical memory bitmap has been zeroed out.");

  uint32_t entry_sz = mem_map->entry_sz;
  terminal_writestring("Entries: ");
  print('l', entries);
  write_newline();

  // WIP record memory map into the physical memory bitmap.
  for(long i = 0; i < entries; i++) {
    map_entry* entry = mem_map + 4*sizeof(uint32_t) + i*entry_sz;
    uint64_t type = entry->type;

    terminal_writestring("Entry type: ");
    print('l', type);
    write_newline();

    // Type of 1 == free, any other value is used in some way.
    if(type != 1){
      uint64_t base = entry->base;
      uint64_t len = entry->length;

      terminal_writestring("Entry base: ");
      print('l', base);
      write_newline();

      terminal_writestring("Entry length: ");
      print('l', len);
      write_newline();

      for(uint64_t addr = base; addr < len; addr++){
        // Mark as used in physical bitmap
        long byte = (addr / FOUR_KB) / 8;
        long bit = ((addr / FOUR_KB) % 8) - 1;
        mm_bitmap[byte] = 1 << bit;
      }
    }
  }

  terminal_writestring("\nDone mapping memory regions.");
}
