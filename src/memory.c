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
size_t mm_bitmap_size;

void mm_init(uint32_t* multiboot) {
  memory_map* mem_map = (memory_map*) get_tag(MEM_MAP, multiboot);
  basic_mem_info* info = (basic_mem_info*) get_tag(BASIC_MEM_INFO, multiboot);
  terminal_writestring("\nMemoryMap found\n");

  mm_bitmap_size = (((info->mem_upper / ONE_KB) + 1) * 256) / 8;
  mm_bitmap = (void*)&_end;
  long entries = ((mem_map->size - 4) * sizeof(uint32_t)) / (mem_map->entry_sz);

  // zero out bitmap.
  size_t size = mm_bitmap_size;
  char* map = mm_bitmap;
  while(size--){
    *map++ = 0x00;
  }

  terminal_writestring("Physical memory bitmap has been zeroed out.");
}
