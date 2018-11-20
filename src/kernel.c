#include <stddef.h>
#include "terminal.h"
#include "multiboot.h"

void kstart(uint32_t* multiboot) {
    /* Initialize terminal interface */
    terminal_initialize();
    terminal_writestring("Hello, kernel World!\n"
                         "MORE TO TEST NEWLINE\n");

    memory_map* memInfo = (memory_map*) get_tag(MEM_MAP, multiboot);

    terminal_writestring("MemoryMap found");
    for(;;){}
}
