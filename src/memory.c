#include "memory.h"
#include "multiboot.h"
#include "terminal.h"
#include <stdbool.h>

#define FRAMES
#define FRAME_SIZE

extern void end;

char* mm_bitmap;
size_t mm_bitmap_size;
size_t mm_bitmap_size;

void mm_init(uint32_t* multiboot) {
  memory_map* mem_map = (memory_map*) get_tag(MEM_MAP, multiboot);
  basic_mem_info* info = (basic_mem_info*) get_tag(BASIC_MEM_INFO, multiboot);
  terminal_writestring("\nMemoryMap found\n");

  // NOTE / TODO for now I only want to find out where the multiboot
  // info is and mark that as used. Will not use low memory ( < 1MiB)
  // so it won't be possible to overwrite the kernel data.

  mm_bitmap_size = (((info->mem_upper / ONE_KB) + 1) * 256) / 8;
  mm_bitmap = (void*) &end;
  int entries = (mem_map->size - 4 * sizeof(uint32_t)) / mem_map->entry_sz;
  for(int i = 0; i < entries; i++) {
    map_entry* entry = (map_entry*) mem_map + (mem_map->entry_sz * i);
  }
}
