#include "vga.h"
#include "io.h"



#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEM     0xB8000

static uint16_t *vga_buffer = (uint16_t *)VGA_MEM;
static int vga_row = 0;
static int vga_col = 0;
static uint8_t vga_color = 0x0F;

void vga_set_color(uint8_t fg, uint8_t bg) {
    vga_color = (bg << 4) | (fg & 0x0F);
}

static uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

void vga_clear(void) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = vga_entry(' ', vga_color);
    }
    vga_row = 0;
    vga_col = 0;
    vga_update_hw_cursor();
}

static void vga_scroll(void) {
    for (int i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) {
        vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
    }
    for (int i = 0; i < VGA_WIDTH; i++) {
        vga_buffer[VGA_WIDTH * (VGA_HEIGHT - 1) + i] = vga_entry(' ', vga_color);
    }
    vga_row = VGA_HEIGHT - 1;
}

void vga_putc(char c) {
    if (c == '\n') {
        vga_col = 0;
        vga_row++;
    } else if (c == '\r') {
        vga_col = 0;
    } else {
        vga_buffer[vga_row * VGA_WIDTH + vga_col] = vga_entry(c, vga_color);
        vga_col++;
        if (vga_col >= VGA_WIDTH) {
            vga_col = 0;
            vga_row++;
        }
    }
    if (vga_row >= VGA_HEIGHT) {
        vga_scroll();
    }
    vga_update_hw_cursor();
}

void vga_puts(const char *str) {
    while (*str) {
        vga_putc(*str++);
    }
}



void vga_backspace(void) {
    if (vga_col > 0) {
        vga_col--;
    } else if (vga_row > 0) {
        vga_row--;
        vga_col = VGA_WIDTH - 1;
    } else {
        return;                    
    }
    
    vga_buffer[vga_row * VGA_WIDTH + vga_col] = vga_entry(' ', vga_color);
    vga_update_hw_cursor();
}



void vga_move_left(void) {
    if (vga_col > 0) vga_col--;
    else if (vga_row > 0) { vga_row--; vga_col = VGA_WIDTH - 1; }
    vga_update_hw_cursor();
}
void vga_move_right(void) {
    if (vga_col < VGA_WIDTH - 1) vga_col++;
    else if (vga_row < VGA_HEIGHT - 1) { vga_row++; vga_col = 0; }
    vga_update_hw_cursor();
}
void vga_move_up(void) {
    if (vga_row > 0) vga_row--;
    vga_update_hw_cursor();
}
void vga_move_down(void) {
    if (vga_row < VGA_HEIGHT - 1) vga_row++;
    vga_update_hw_cursor();
}


void vga_update_hw_cursor(void) {
    uint16_t pos = vga_row * VGA_WIDTH + vga_col;
    outb(0x3D4, 0x0F);
    outb(0x3D5, pos & 0xFF);
    outb(0x3D4, 0x0E);              
    outb(0x3D5, (pos >> 8) & 0xFF);
}


