[BITS 16]
[ORG 0x7C00]

mov ax,0x3
int 10h
mov ah,0x0e
mov al,'L'
int 0x10
xor ah,ah
xor al,al
mov ah,0x0e
mov al,'o'
int 0x10
;call hang
mov al,'a'
int 0x10
mov al,'d'
int 0x10
mov al,'i'
int 0x10
mov al,'n'
int 0x10
mov al,'g'
int 0x10
mov al,'.'
int 0x10
int 0x10
int 0x10
mov ax,5632
mov ds,ax
mov es,ax
mov fs,ax
mov gs,ax
jmp 1200:2200h
times 510 - ($ - $$) db 0
dw 0xAA55
times 1000h db 0
