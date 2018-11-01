CC = clang
CFLAGS = -c -ffreestanding -target x86_64-unknown-none -nostdlib \
	-Wall -Wextra -fno-exceptions -fno-rtti
asmsrc = $(wildcard src/*.asm)
asmobj = $(asmsrc:.asm=.o)
csrc = $(wildcard src/*.c)
cobj = $(csrc:.c=.o)

.PHONY: clean run

kernel: $(asmobj) $(cobj)
	@ld --gc-sections -n -T src/linker.ld -o brick \
		$(asmobj) $(cobj)
	@mkdir -p isofiles/boot/grub
	@cp grub.cfg isofiles/boot/grub/
	@cp brick isofiles/boot/kernel.bin
	@grub-mkrescue -o brick.iso isofiles


%.o: %.asm
	@nasm -felf64 $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ $<

clean:
	@rm -rf isofiles
	@rm brick*
	@rm -f src/*.o

run:
	qemu-system-x86_64 -m 4G -cdrom brick.iso
