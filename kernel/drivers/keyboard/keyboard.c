#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "keyboard.h"
#include "io.h"

#define STATUS_PORT 0x64
#define DATA_PORT   0x60
#define STATUS_DATA 0x01

static bool shift_down = false;
static bool ctrl_down  = false;
static bool caps_lock  = false;
static int extended = 0;

static const char kb_chars[SC_MAX] = {
    [0x01] = 27,
    [0x02] = '1', [0x03] = '2', [0x04] = '3', [0x05] = '4',
    [0x06] = '5', [0x07] = '6', [0x08] = '7', [0x09] = '8',
    [0x0A] = '9', [0x0B] = '0', [0x0C] = '-', [0x0D] = '=',
    [0x0E] = '\b',
    [0x0F] = '\t',
    [0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r',
    [0x14] = 't', [0x15] = 'y', [0x16] = 'u', [0x17] = 'i',
    [0x18] = 'o', [0x19] = 'p', [0x1A] = '[', [0x1B] = ']',
    [0x1C] = '\n',
    [0x1E] = 'a', [0x1F] = 's', [0x20] = 'd', [0x21] = 'f',
    [0x22] = 'g', [0x23] = 'h', [0x24] = 'j', [0x25] = 'k',
    [0x26] = 'l', [0x27] = ';', [0x28] = '\'', [0x29] = '`',
    [0x2C] = 'z', [0x2D] = 'x', [0x2E] = 'c', [0x2F] = 'v',
    [0x30] = 'b', [0x31] = 'n', [0x32] = 'm', [0x33] = ',',
    [0x34] = '.', [0x35] = '/',
    [0x39] = ' ',
};

typedef struct {
    uint8_t scancode;
    const char *name;
} KeyName;

static const KeyName kb_names[] = {
    {0x01, "Escape"},   {0x0E, "Backspace"}, {0x0F, "Tab"},
    {0x1C, "Enter"},    {0x1D, "Left Ctrl"}, {0x2A, "Left Shift"},
    {0x36, "Right Shift"}, {0x38, "Left Alt"}, {0x3A, "Caps Lock"},
    {0x39, "Space"},    {0x2B, "Backslash"},
};

bool kb_has_key(void) {
    return (inb(STATUS_PORT) & STATUS_DATA) != 0;
}

uint8_t kb_read_raw(void) {
    if (!kb_has_key()) {
        return 0;
    }
    return inb(DATA_PORT);
}

KeyEvent kb_read_event(void) {
    KeyEvent ev;
    uint8_t raw = kb_read_raw();

    ev.released = (raw & SC_RELEASE) != 0;
    ev.scancode = raw & ~SC_RELEASE;
    if (ev.scancode >= SC_MAX) {
        ev.scancode = 0;
    }

    switch (ev.scancode) {
        case 0x2A:
        case 0x36:
            shift_down = !ev.released;
            break;
        case 0x1D:
            ctrl_down = !ev.released;
            break;
        case 0x3A:
            if (!ev.released) {
                caps_lock = !caps_lock;
            }
            break;
        default:
            break;
    }

    return ev;
}

bool kb_is_shift(void) { return shift_down; }
bool kb_is_caps(void)  { return caps_lock; }

char kb_scancode_to_char(uint8_t scancode) {
    if (scancode >= SC_MAX) {
        return 0;
    }

    char c = kb_chars[scancode];
    if (c == 0 || c == 27) {
        return 0;
    }

    bool upper = kb_is_shift();
    if (kb_is_caps() && c >= 'a' && c <= 'z') {
        upper = !upper;
    }

    if (upper && c >= 'a' && c <= 'z') {
        c = (char)(c - 'a' + 'A');
    }

    return c;
}

const char *kb_scancode_name(uint8_t scancode) {
    const size_t n = sizeof(kb_names) / sizeof(kb_names[0]);

    for (size_t i = 0; i < n; i++) {
        if (kb_names[i].scancode == scancode) {
            return kb_names[i].name;
        }
    }
    return NULL;
}
