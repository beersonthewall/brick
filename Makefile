CC=clang-6.0
CFLAGS= -c -ffreestanding -target x86_64-unknown-none -nostdlib \
	-Wall -Wextra -fno-exceptions -fno-rtti -Iinclude -Isrc \
	-mno-sse -mno-mmx -mno-avx -g -fno-omit-frame-pointer
asmsrc = $(wildcard src/*.asm)
asmobj = $(asmsrc:.asm=.o)
csrc = $(wildcard src/*.c)
cobj = $(csrc:.c=.o)

.PHONY: clean run

kernel: $(asmobj) $(cobj) $(libcobj)
	@ld -n -T src/linker.ld -o brick \
		$(asmobj) $(cobj) $(libcobj)
	@mkdir -p isofiles/boot/grub
	@cp grub.cfg isofiles/boot/grub/
	@cp brick isofiles/boot/kernel.bin
	@grub-mkrescue -o brick.iso isofiles


%.o: %.asm
	@nasm -felf64 -F dwarf $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ $<

clean:
	@rm -rf isofiles
	@rm brick*
	@rm -f src/*.o

run:
	make
	qemu-system-x86_64 -m 2G -cdrom brick.iso

debug:
	make
	qemu-system-x86_64 -s -S -d int,cpu_reset,guest_errors -m 2G -cdrom brick.iso
