CC = clang
asmsrc = $(wildcard src/*.asm)
obj = $(asmsrc:.asm=.o)

.PHONY: clean run

kernel: $(obj)
	@ld -n -T src/linker.ld -o brick \
		$(obj)
	@mkdir -p isofiles/boot/grub
	@cp grub.cfg isofiles/boot/grub/
	@cp brick isofiles/boot/kernel.bin
	@grub-mkrescue -o brick.iso isofiles
	@rm src/*.o

%.o: %.asm
	@nasm -felf64 $< -o $@

clean:
	@rm -rf isofiles
	@rm brick*
	@rm -f src/*.o

run:
	qemu-system-x86_64 -m 4G -cdrom brick.iso
