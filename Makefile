C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

car: clean all run
	clean
	all
	run

all: os-image

run: all
	qemu-system-i386 -fda os-image

os-image: boot/bootsect.bin kernel.bin
	cat $^ > os-image

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary -m elf_i386

%.o: %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@ -m32

%.o: %.asm
	nasm $< -f elf -o $@

%.bin:%.asm
	nasm $< -f bin -o $@

clean:
	rm -fr *.bin *.o os-image *.map *.dis
	rm -fr kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@


