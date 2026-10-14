#include "colour.h"
#include "keyboard.h"
#include "vga.h"


void kernel_main() {
 while (true) {
  if (kb_has_key()) {
    KeyEvent ev = kb_read_event();
    if (!ev.released) {
        char c = kb_scancode_to_char(ev.scancode);
        if (c != 0) vga_putc(c);
     }
   }
 }
}
