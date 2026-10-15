#include "vga.h"

void colour_reset(void) {
  vga_set_color(0x0F, 0x00);
}


void colour_r(const char *str) {
  vga_set_color(0x04, 0x00);
  vga_puts(str);
  colour_reset();
}

void colour_b(const char *str) {
  vga_set_color(0x01, 0x00);
  vga_puts(str);
  colour_reset();
}

void colour_g(const char *str) {
  vga_set_color(0x02, 0x00);
  vga_puts(str);
  colour_reset();
}


void colour_a(const char *str) {
  vga_set_color(0x03, 0x00);
  vga_puts(str);
  colour_reset();
}
