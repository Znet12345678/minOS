[bits 16]
[org 0x7C00]
_start:mov ah,0x0e
mov al,'L'
int 0x10
mov al,'o'
int 0x10
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
mov al,0x0a
int 0x10
mov ah,3
mov bh,0
int 0x10
mov dl,0
mov ah,2
int 0x10
floppy1:mov al,'F'
mov ah,0x0e
int 0x10
mov al,'D'
int 0x10
mov al,'A'
int 0x10
mov al,' '
int 0x10
mov al,0x0a
int 0x10
mov ah,3
mov bh,0
int 0x10
mov dl,0
mov ah,2
int 0x10
xor ah,ah
xor al,al
mov dl,0
mov ah,0x02
mov al,4
mov ch,0
mov cl,2
mov dh,0
mov bx,0x600
int 0x13
cmp ah,0
jz success
floppy2:mov al,'F'
mov ah,0x0e
int 0x10
mov al,'D'
int 0x10
mov al,'B'
int 0x10
mov al,' '
int 0x10
mov al,0x0a
int 0x10
mov ah,3
mov bh,0
int 0x10
mov dl,0
mov ah,2
int 0x10
mov al,4
mov ah,1
mov dl,1
mov ah,0x02
mov al,4
mov ch,0
mov cl,2
mov dh,0
mov bx,0x600
int 0x13
cmp ah,0
jz success
hd1:mov al,'H'
mov ah,0x0e
int 0x10
mov al,'D'
int 0x10
mov al,'A'
int 0x10
mov al,' '
int 0x10
mov al,0x0a
int 0x10
mov ah,3
mov bh,0
int 0x10
mov dl,0
mov ah,2
int 0x10
mov al,4
mov ah,0x02
mov dl,0x80
mov ah,0x02
mov al,4
mov ch,0
mov cl,2
mov dh,0
mov bx,0x600
int 0x13
cmp ah,0
jz success
hd2:
mov al,'H'
mov ah,0x0e
int 0x10
mov al,'D'
int 0x10
mov al,'B'
int 0x10
mov al,' '
int 0x10
mov al,0x0a
int 0x10
mov ah,3
mov bh,0
int 0x10
mov dl,0
mov ah,2
int 0x10

mov dl,0x81
mov ah,4
mov al,1
mov ah,0x02
mov al,4
mov ch,0
mov cl,2
mov dh,0
mov bx,0x600
int 0x13
cmp ah,0
jz success
error:mov ah,0x0e
mov al,'E'
int 0x10
mov al,'r'
int 0x10
int 0x10
mov al,'o'
int 0x10
mov al,'r'
int 0x10
e_loop:
JMP e_loop
success:mov [0x500],dl
xor al,al
xor dl,dl
xor ah,ah
xor bx,bx
xor dh,dh
xor cl,cl
xor ch,ch
xor al,al
xor ah,ah
JMP 0x600
times 510 - ($ - $$) db 0
dw 0xaa55
mov ah,0x0e
mov al,'.'
int 0x10
xor ah,ah
xor al,al
xor bh,bh
xor ah,ah
xor al,al
xor ch,ch
xor dh,dh
xor cl,cl
xor dl,dl
xor bx,bx
mov bh,0
mov ah,2
mov al,1
mov ch,0
mov dh,0
mov cl,2
mov dl,[0x500]
mov bx,0x100
loop:mov ah,0x0e
mov al,'.'
int 0x10
push cx
JMP clean
return:pop cx
xor ah,ah
xor al,al
mov ah,2
mov al,1
int 0x13
cmp ah,0
jnz _error
xor bh,bh
mov bh,[0x100]
cmp bh,0x0f
jz check
cmp cl,63
JE end
inc cl
JMP loop

clean:
mov cx,0
_clean:mov bx,[0x100]
mov [bx],byte 0
inc bx
inc cx
cmp cx,512
JE return
JMP _clean
check:mov al,'!'
mov ah,0x0e
int 0x10
mov bh,[0x101]
cmp bh,0x1f
jz end
mov al,1
mov ah,2
inc cl
jmp loop
end:mov ah,0x0e
mov al,'P'
int 0x10
mov al,'a'
int 0x10
mov al,'r'
int 0x10
mov al,'s'
int 0x10
mov al,'i'
int 0x10
mov al,'n'
int 0x10
mov al,'g'
int 0x10
mov al,' '
int 0x10
mov al,'E'
int 0x10
mov al,'L'
int 0x10
mov al,'F'
int 0x10
_loop:
jmp _loop
_error:
mov ah,0x0e
mov al,'E'
int 0x10
mov al,'R'
int 0x10
int 0x10
mov al,'O'
int 0x10
mov al,'R'
int 0x10
times 4096 - ($ - $$) db 0
dw 0x1f0f
