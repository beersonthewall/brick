#include "terminal.h"

void kstart(long multiboot) {
    /* Initialize terminal interface */
    terminal_initialize();

    terminal_writestring("Hello, kernel World!\n"
                         "MORE TO TEST NEWLINE");
  for(;;){
  }
}
