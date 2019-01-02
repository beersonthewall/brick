#include <stddef.h>
#include "terminal.h"
#include "multiboot.h"
#include "memory.h"

void kstart(uint32_t* multiboot) {
    /* Initialize terminal interface */
    terminal_initialize();
    terminal_writestring("Hello, kernel World!\n"
                         "MORE TO TEST NEWLINE\n");

    int testInt = 1000;
    print('d', testInt);

    //    init(multiboot);

    for(;;){}
}
