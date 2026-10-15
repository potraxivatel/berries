#include "vga.h"


int calculate(char symvol, int num1, int num2) {
  if (symvol == '-') {
    num1 - num2;
    vga_puts("Result: %d\n", num1 + num2);
  } else if (symvol == '+') {
    num1 + num2;
    vga_puts("Result: %d\n", num1 + num2);
  } else if (symvol == '*') {
    num1 * num2;
    vga_puts("Result: %d\n", num1 + num2);
  } else if (symvol == '/') {
    if (num2 != 0) {
      num1 / num2;
      vga_puts("Result: %d\n", num1 + num2);
    } else {
      return 0;
    }
  }
  return 0;
}


