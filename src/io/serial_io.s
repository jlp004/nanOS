global outb
global inb

; outb - sends a byte to an I/O port
; stack: [esp + 8] = the data byte
;        [esp + 4] = the I/O port
;        [esp    ] = return address
outb:
    mov edx, [esp + 4]       ; Load the port (16-bit) from the stack into edx
    mov al, [esp + 8]        ; Load the data (8-bit) from the stack into al
    out dx, al               ; Output the byte in al to the port in dx
    ret


; inb - returns a byte from an I/O port
; stack: [esp + 4] = Address of the I/O port
;        [esp    ] = return address  
inb:
    mov dx, [esp+4]
    in al, dx
    ret
