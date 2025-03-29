global loader
MAGIC_NUMBER    equ 0x1BADB002
FLAGS           equ 0x0
CHECKSUM        equ -MAGIC_NUMBER

KERNEL_STACK_SIZE equ 4096

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM


loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; move esp pointer to the end of the reserved stack space
    mov eax, 0xCAFEBABE                         ; moving a value into eax to check logs to compare if kernel launched
.loop:
    jmp .loop

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE                      ; reserve stack space for the kernel    
