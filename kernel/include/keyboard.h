#ifdef KEYBOARD_H
#define KEYBOARD_H

#include "stdint.h"

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

uint8_t keyboard_read(void);
void keyboard_write(uint8_t value);

#endif 
