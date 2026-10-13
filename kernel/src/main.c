#include "vga.h"

void kernel_main(void) {
    vga_clear();
    vga_set_color(0x0A, 0x00);   // зелёный текст
    vga_puts("  Berries OS v0.0.1\n");
    vga_puts("  ===================\n\n");
    vga_set_color(0x0F, 0x00);   // белый текст
    vga_puts("  Kernel loaded successfully!\n");
    vga_puts("  Hello from Berries!\n");
}
