#ifndef IO_H
#define IO_H

#include <stdint.h>

// Реализованы в drivers/keyboard.asm (NASM, stdcall-подобный пролог)
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

#endif