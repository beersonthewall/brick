writing a simple kernel to learn.

Boot code in boot.asm, long_mode_start.asm, and multiboot_header.asm is
from https://os.phil-opp.com/first-edition/.

Terminal code modified to support newline from:
https://wiki.osdev.org/Bare_Bones

Dependencies / Tools:
grub-mkrescue and an appropriate version of xorriso (I think 1.29 or later).
qemu:
sudo apt-get install qemu-kvm qemu virt-manager virt-viewer libvirt-bin
