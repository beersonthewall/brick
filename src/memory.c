#include "memory.h"
#include "multiboot.h"
#include "terminal.h"
#include <stdbool.h>

#define FRAMES
#define FRAME_SIZE 

char* bootstrap_mmap[];

void init(uint32_t* multiboot) {
  memory_map* mem_info = (memory_map*) get_tag(MEM_MAP, multiboot);

  // NOTE / TODO for now I only want to find out where the multiboot
  // info is and mark that as used. Will nbot use low memory ( < 1MiB)
  // so it won't be possible to overwrite the kernel data.

  //  elf_symbols* elf_sym = get_tag(ELF_SYMBOLS, multiboot);

  int entries = (mem_info->size - 4 * sizeof(uint32_t)) / mem_info->entry_sz;
  map_entry* last_entry = (map_entry*) multiboot + 4 * sizeof(uint32_t);
  last_entry += entries - 1;
  uint64_t total_size = last_entry->base + last_entry->length;

  int s = 20000;
  int frames[s];

  for(int i = 0; i < s; i++){
    frames[i] = i;
  }

  terminal_writestring("MemoryMap found");
}
