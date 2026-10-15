CC      = gcc
ASM     = nasm
LD      = ld

CFLAGS   = -m32 -ffreestanding -fno-stack-protector -nostdlib -Iinclude -Idrivers
ASMFLAGS = -f elf32
LDFLAGS  = -m elf_i386 -T linker.ld -nostdlib

SRC     = drivers/keyboard/keyboard.c src/main.c drivers/vga/vga.c etc/utility/colour.c
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

# База компиляции для clangd: без неё редактор не знает про -Iinclude,
# -m32 и -ffreestanding и «не догадывает». Пути внутри .clangd относительные,
# clangd резолвит их от каталога, указанного в "directory" здесь.
compile_commands.json: $(SRC)
	@printf '[\n' > $@
	@first=1; \
	for f in $(SRC); do \
		if [ $$first -eq 0 ]; then printf ',\n' >> $@; fi; \
		first=0; \
		printf '  {"directory": "$(CURDIR)", "file": "%s/%s", "command": "$(CC) $(CFLAGS) -c %s -o %s"}' \
			"$(CURDIR)" "$$f" "$$f" "$${f%.c}.o" >> $@; \
	done; \
	printf '\n]\n' >> $@
	@printf 'cdb: %s entries\n' "$(words $(SRC))"

cdb: compile_commands.json

.PHONY: all clean cdb
