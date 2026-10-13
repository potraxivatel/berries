#include "vga.h"

void kernel_main(void) {
    vga_clear();
    int i = 0;
    while (i < 10) {
      if (i < 10) {
        vga_puts("Hello from berries kernel!!!\n");
        i = i + 1;
      } else {
        break;
      }
    }
}


