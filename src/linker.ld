ENTRY(start)

SECTIONS {
         . = 1M;
         _start = .;
         .boot :
         {
               KEEP(*(.multiboot_header))
         }

         .text :
         {
               *(.text)
         }

         .rodata :
         {
               *(.rodata)
         }

         .data :
         {
               *(.data)
         }

         .bss :
         {
               *(.bss)
         }
         _end = .;
}
