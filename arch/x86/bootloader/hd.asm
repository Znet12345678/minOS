[BITS 16]
times 1024 db 0
mov ah,0x0e
mov al,'S'
int 0x10
times 8192 db 0
