#include <stddef.h>
#include "terminal.h"
#include "multiboot.h"
#include "memory.h"

void init(uint32_t* multiboot){
  
}

void kstart(uint32_t* multiboot) {
  /* Initialize terminal interface */
  terminal_initialize();
  terminal_writestring("Hello, kernel World!\n"
                       "MORE TO TEST NEWLINE\n");
  mm_init(multiboot);
  for(;;){}
}
