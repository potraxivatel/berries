#include "vga.h"

void colour_r(const char *str) {
  vga_set_color(0x04, 0x00);
  vga_puts(str);
}

void colour_b(const char *str) {
  vga_set_color(0x01, 0x00);
  vga_puts(str);
}

void colour_g(const char *str) {
  vga_set_color(0x02, 0x00);
  vga_puts(str);
}

