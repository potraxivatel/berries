#include "colour.h"
#include "keyboard.h"
#include "vga.h"

#define SC_ESCAPE 0x01

static void delay(void) {
    volatile unsigned int i = 0;
    while (i < 30000000) i++;
}



void kernel_main() {
  vga_clear();

  vga_puts("berries kernel. v0.4.0\n");


 while (true) {
  if (kb_has_key()) {
    KeyEvent ev = kb_read_event();

    if (ev.scancode == SC_ESCAPE && !ev.released) {
      colour_r("Bye! \n");
      delay();
      return;
    }

    if (!ev.released) {
        char c = kb_scancode_to_char(ev.scancode);
        if (c != 0) vga_putc(c);
     }
   }
  }
}
