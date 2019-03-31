ENTRY(start)

SECTIONS {
         _begin = .;
         . = 1M;
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
