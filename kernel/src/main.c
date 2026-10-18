#include "colour.h"
#include "keyboard.h"
#include "vga.h"
#include <stdint.h>

#define SC_ESCAPE 0x01

void calibrate_tsc(void);
void kernel_sleep(uint32_t seconds);

void kernel_main() {
  calibrate_tsc();
  vga_clear();

  vga_puts("berries kernel. v0.5.0\n");

  while (true) {
    if (kb_has_key()) {
      KeyEvent ev = kb_read_event();

      if (ev.scancode == SC_ESCAPE && !ev.released) {
        colour_r("Balling out...\n");
        kernel_sleep(7);
        colour_g("Y!!!");
        return;
      }

      if (!ev.released) {
        char c = kb_scancode_to_char(ev.scancode);
        if (c != 0)
          vga_putc(c);
      }
    }
  }
}
