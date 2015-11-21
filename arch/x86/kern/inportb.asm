;
; Summary: inportb.asm
; *inportb implementation for libx86*
;
; Author:
;     Marcel Sondaar
;
; License:
;     Public Domain
;
 
SECTION .text
 
global inportb
global inb
global outportb
global outb 
global inw
global outw
;
; Function: inportb
; reads a byte from an x86 i/o port
;
; in:
;     - Stack(1) = port to access
;
; out:
;     Return = read value
;
 
inportb:    MOV DX, [ESP+1*4]           ; DX = stack(1)
            IN byte AL, DX              ; AL = result
            RET
inb:	MOV DX, [ESP+1*4]
	IN byte AL, DX
	RET
outportb:
	 MOV DX, [ESP+1*4]           ; DX = stack(1)
         MOV AL, [ESP+2*4]           ; AL = stack(2)
         OUT DX, AL                  ; write
         RET
outb:
	 MOV DX, [ESP+1*4]           ; DX = stack(1)
         MOV AL, [ESP+2*4]           ; AL = stack(2)
         OUT DX, AL                  ; write
         RET

