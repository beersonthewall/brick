global long_mode_start

section .text
bits 64
long_mode_start:

  xor ax, ax
  mov ss, ax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  extern kstart
  call kstart

  mov rax, 0x2f592f412f4b2f4f
  mov qword [0xb8000], rax
  hlt
