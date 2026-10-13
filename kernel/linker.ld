ENTRY(_start)

SECTIONS {
    . = 1M;   /* Ядро грузится по адресу 1 МБ */

    .text : {
        *(.multiboot)   /* Заголовок должен быть первым! */
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}
