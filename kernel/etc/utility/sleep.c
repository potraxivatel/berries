#include "vga.h"


//int second_handler() что бы не считать млсек а сразу напаисать 3 3с = 30000

int sleep(volatile unsigned t) {
  volatile unsigned int i = 0;
  while (i < t) {
    i++;
  }
  return 0;
}
