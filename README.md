To run the code, I recommend you run it in a Ubuntu virtual machine with qemu emulator. This is coding envrionment I have success with. I had trouble compiling running the bochs emulator in macOS. 

You will need to install qemu emulator inside your Ubuntu virtual machine.

The content of this kernel follows the tutorial from here: http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf and then here https://github.com/cfenollosa/os-tutorial up to 21-shell

Here are some often used commands during my development:

# clean, compile and run the kernel in emulator:

make car

# compile asm to bin:

nasm boot_sect.asm -f bin -o boot_sect.bin

# run in emulator:

qemu-system-i386 -fda os-image

# combile asm to bin and run:

nasm boot_sect.asm -f bin -o boot_sect.bin; qemu-system-i386 -fda boot_sect.bin

# compile c to o and to binary:

gcc -ffreestanding -c kernel.c -o kernel.o -m32;
ld -o kernel.bin -Ttext 0x1000 --oformat binary kernel.o;

# put kernel and boot_sect together into a image

cat boot_sect.bin kernel.bin > os-image

# run the image in emulator

qemu-system-i386 -fda os-image

# compile asm to o file

nasm kernel_entry.asm -f elf -o kernel_entry.o

# link kernel entry and kernel to one bin 

ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary -m elf_i386

# compile asm to bin and run in emulator:

nasm boot_sect18.asm -f bin -o boot_sect.bin; qemu-system-i386 -fda boot_sect.bin
