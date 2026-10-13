MBOOT_MAGIC     equ 0x1BADB002
MBOOT_FLAGS     equ 0x00000003
MBOOT_CHECKSUM  equ -(MBOOT_MAGIC + MBOOT_FLAGS)

section .multiboot
align 4
    dd MBOOT_MAGIC
    dd MBOOT_FLAGS
    dd MBOOT_CHECKSUM


; Ядру нужен стек, чтобы вызывать функции
section .bss
align 16
stack_bottom:
    resb 16384      
stack_top:


section .text
global _start:function (_start.end - _start)
_start:
    
    mov esp, stack_top

    extern kernel_main
    call kernel_main

    
    cli
.hang:
    hlt
    jmp .hang
.end:
