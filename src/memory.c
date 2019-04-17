#include "memory.h"
#include "multiboot.h"
#include "terminal.h"
#include <stdbool.h>

#define FRAMES
#define FRAME_SIZE

// Linker tag for end of the kernel. Placed immediately below the stack.
extern void _end;

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
  terminal_writestring("\nMemoryMap found\n");


  uint32_t msize = *multiboot;
  long entries = ((mem_map->size - 4) * sizeof(uint32_t)) / (mem_map->entry_sz);

  terminal_writestring("Multibootptr: ");
  print('l', multiboot);
  write_newline();

  terminal_writestring("Endptr: ");
  print('l', &_end);
  write_newline();

  terminal_writestring("Multibootinfo sz: ");
  print('d', msize);
  write_newline();

  terminal_writestring("entries: ");
  print('l', entries);
  write_newline();

  terminal_writestring("bitmap size: ");
  print('l', mm_bitmap_size);
  write_newline();

  mm_bitmap_size = (((info->mem_upper / ONE_KB) + 1) * 256) / 8; // # pages / 8
  // Address of the mutliboot struct + it's size. Avoids overwriting it.
  // This "works":
  mm_bitmap = (void*) &_end;
  // but this does not:
  //mm_bitmap = (void*)(multiboot + msize);
  // zero out bitmap.
  size_t size = mm_bitmap_size;
  char* map = mm_bitmap;
  while(size--){
    *map++ = 0x00;
  }
  terminal_writestring("Physical memory bitmap has been zeroed out.");

  for(long i = 0; i < entries; i++) {
    map_entry* entry = (mem_map + 4*4);
    uint64_t base = entry->base;
    uint64_t len = entry->length;

    // Mark as used in physical bitmap
    long byte = (base / FOUR_KB) / 8;
    long bit = ((base / FOUR_KB) % 8) - 1;
    mm_bitmap[byte] = 1 << bit;
  }
  terminal_writestring("\nDone mapping memory regions.");
}
