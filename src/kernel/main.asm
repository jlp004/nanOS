org 0x0
bits 16

%define ENDL 0x0D, 0x0A

start: 
  ; call print hello world
  mov si, msg_hello
  call puts

.halt:
  cli
  hlt

;
; prints string to the screen
; params:
;   -ds:si points to string
;
puts:
  ; save registers we will modify
  push si 
  push ax

.loop:
  lodsb         ; loads next character in al
  or al, al     ; verify if next character is null
  jz .done      ; jump to .done label if zero flag set
  mov ah, 0x0e  ; call bios interrupt
  mov bh, 0
  int 0x10
  jmp .loop

.done:
  pop ax
  pop si 
  ret


msg_hello: 
  db 'Hello World 2!'
  db ENDL                   ;defined newline
  db 0                      ;null term
