#include <stdbool.h>
#include "multiboot.h"
#include "terminal.h"

/*
 * Searches for the given tag type in the provided multiboot information
 * structure. Returns a pointer to that structure or zero if it was not found.
 */
void* get_tag(enum tag tg, uint32_t* multiboot) {

  uintptr_t loc = 2*sizeof(uint32_t) + (uintptr_t) multiboot;

  void* found_tg = 0;
  bool at_end = false;
  while(!at_end) {
    uint32_t type = *((uint32_t*)loc);
    uint32_t sz = *((uint32_t*) (loc + sizeof(uint32_t)));

    if(type == 0 && sz == 8) {
      at_end = true;
    }
    if(type == tg) {
      found_tg = (uint32_t*) loc;
      break;
    }

    loc += sz;
    if(loc % 8 != 0) {
      loc += 8 - (loc % 8);
    }
  }

  return found_tg;
}
