global loader
extern fb_write_cell

MAGIC_NUMBER    equ 0x1BADB002
FLAGS           equ 0x0
CHECKSUM        equ -MAGIC_NUMBER 


section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    mov ebx, 0xCAFEBABE
    push dword 0x8
    push dword 0x2
    push dword 0x41
    push dword 0x0
    call fb_write_cell
.loop:
    jmp .loop           

