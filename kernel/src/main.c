#include "colour.h"
#include "keyboard.h"
#include "vga.h"
#include "sleep.h"


#define SC_ESCAPE 0x01


void kernel_main() {
  vga_clear();

vga_puts("berries kernel. v0.4.0\n");
  
 while (true) {
  if (kb_has_key()) {
    KeyEvent ev = kb_read_event();

    if (ev.scancode == SC_ESCAPE && !ev.released) {
      colour_r("Balling out...\n");
      sleep(30000000);
      colour_g("Y!!!");
      return;
    }

    if (!ev.released) {
        char c = kb_scancode_to_char(ev.scancode);
        if (c != 0) vga_putc(c);
     }
   }
  }
}

