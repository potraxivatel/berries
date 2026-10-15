#ifndef VGA_H
#define VGA_H

#include <stdint.h>

void vga_clear(void);
void vga_putc(char c);
void vga_puts(const char *str);
void vga_set_color(uint8_t fg, uint8_t bg);
void vga_backspace(void);
void vga_move_left(void);
void vga_move_right(void);
void vga_move_up(void);
void vga_move_down(void);
void vga_update_hw_cursor(void);

#endif
