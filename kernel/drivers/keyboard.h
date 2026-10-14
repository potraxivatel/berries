#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

// Биты скан-кода
#define SC_RELEASE   0x80   // бит 7: 1 = отпускание, 0 = нажатие
#define SC_MAX       128    // размер таблицы (8 бит)

// Есть ли в буфере клавиатуры непрочитанный байт?
bool kb_has_key(void);

// Читает сырой скан-код из порта 0x60.
// Возвращает 0, если данных нет.
uint8_t kb_read_raw(void);

// Разбирает событие: нажатие или отпускание.
typedef struct {
    uint8_t scancode;   // скан-код без бита 7
    bool released;      // true = отпустили, false = нажали
} KeyEvent;

KeyEvent kb_read_event(void);

// Текущее состояние модификаторов (обновляется при чтении событий)
bool kb_is_shift(void);

// Символ по раскладке US QWERTY с учётом Shift.
// Возвращает 0, если для этого скан-кода нет символа.
char kb_scancode_to_char(uint8_t scancode);

// Имя клавиши для отладки, например "Left Shift".
// Возвращает NULL, если не найдено.
const char *kb_scancode_name(uint8_t scancode);

// Заблокирован ли Caps Lock?
bool kb_is_caps(void);

#endif