#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define SC_RELEASE   0x80
#define SC_MAX       128

typedef struct {
    uint8_t scancode;
    bool released;
} KeyEvent;

bool kb_has_key(void);
uint8_t kb_read_raw(void);
KeyEvent kb_read_event(void);
char kb_scancode_to_char(uint8_t scancode);
const char *kb_scancode_name(uint8_t scancode);
bool kb_is_shift(void);
bool kb_is_caps(void);

#endif