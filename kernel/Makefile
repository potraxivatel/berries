CC      = gcc
ASM     = nasm
LD      = ld

CFLAGS   = -m32 -ffreestanding -fno-stack-protector -nostdlib -Iinclude -Idrivers
ASMFLAGS = -f elf32
LDFLAGS  = -m elf_i386 -T linker.ld -nostdlib

SRC     = drivers/keyboard.c src/main.c src/vga/vga.c src/vga/colour.c
ASM_SRC = boot/boot.asm drivers/asm/keyboard.asm
OBJ     = $(SRC:.c=.o) $(ASM_SRC:.asm=.o)

all: berries-kernel

berries-kernel: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f $(OBJ) berries-kernel

.PHONY: all clean
