
resb 7C00h
jmp short _start

global _start
extern Start
;.text
section .text
;.text
Message: db 'Loading..._'
_start:
	;mov ax,07C0h
	;add ax,20h
	;mov ss,ax
	;mov sp,4096
	;mov ax,07C0h
	;mov si,message
	;mov ds,ax
	;mov si,message
	;mov ah,0Eh
	JMP Start
	mov bx,000Fh
	mov cx,1
	xor dx,dx
	mov ds,dx
	cld
Print:	mov esi,Message
Char:	mov ah,2
	int 10h
	lodsb
	mov ah,9
	int 10h
	cmp dl,80
	jne Skip
	xor dl,dl
	inc dh
	cmp dh,25
	jne Skip
	xor dh,dh
Skip: cmp si,'_'
	jne Char
	jmp Print
	JMP Start
	cli
	hlt
message: db 'Loading..._'
.pc:
	lodsb
	cmp al,0
	je .done
	int 10h
	jmp .pc
;data:
;	message db 'Loading...'
.done:
	ret
	times 1474560  -($-$$) db 0
	dw 0xAA55

