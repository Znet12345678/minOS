;License: http://creativecommons.org/licenses/by-sa/2.0/uk/
;Some code modified from Napalm's code @http://www.rohitab.com/discuss/topic/35103-switch-between-real-mode-and-protected-mode/
[bits 32]
global initgui

%define INITGUI_BASE 0x7C00
%define REBASE(x) (((x) - phase2) + INITGUI_BASE)
%define GDTENTRY(x) ((x) &lt;< 3)
%define CODE32  GDTENTRY(1)
%define DATA32  GDTENTRY(2)
%define CODE16  GDTENTRY(3)
%define DATA16  GDTENTRY(4)
%define STACK16 (INITGUI_BASE - 13)
section .text
initgui:use32
	cli
	pusha
	mov esi,phase2
	mov edi,INITGUI_BASE
	mov ecx, (initgui_end - phase2)
	cld
	rep movsb
	jmp INITGUI_BASE
phase2:use32
	mov [REBASE(ptr1)],esp
	sidt [REBASE(ptr2)]
	sgdt [REBASE(ptr2)]
	lgdt [REBASE(ptr3)]
	lea esi, [esp + 0x24]
	lodsd
	mov [REBASE(ib)],al
	mov esi,[esi]
	mov edi,STACK16
	mov ecx,13
	mov esp,edi
	rep movsb
	jmp word 0x18:REBASE(pmode)
pmode:use16
	mov ax,0x20
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	mov eax,cr0
	and al, ~0x01
	mov cr0,eax
	jmp word 0x0000:REBASE(rmode)
rmode:use16
	xor ax,ax
	mov ds,ax
	mov ss,ax
	lidt [REBASE(ptr3)]
	mov bx,0x0870
	call reset
	mov ah,00h
	mov al,13
	sti
	int 0x10
;	db 0xCD
ib:	db 0x00
	cli
	xor sp,sp
	mov ss,sp
	mov sp,INITGUI_BASE
	mov bx,0x2028
	mov eax,cr0
	call reset
	inc eax
	mov cr0,eax
	jmp dword 0x08:REBASE(pmode32)
pmode32:use32
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	lgdt [REBASE(ptr2)]
	lidt [REBASE(ptr2)]
	mov esp,[REBASE(ptr1)]
	mov esi,STACK16
	lea edi, [esp+0x28]
	mov edi,[edi]
	mov ecx,2
	cld
	rep movsb
	popa
	sti
	ret
reset:
	push ax
	mov al,0x11
	out 0x20,al
	out 0xA0,al
	mov al,bh
	out 0x21,al
	mov al,bl
	out 0xA1,al
	mov al,0x04
	out 0x21,al
	shr al, 1
	out 0xA1,al
	shr al,1
	out 0x21, al
	out 0xA1,al
	pop ax
	ret
	
ptr1:
	dd 0x00000000
ptr2:
	dw 0x0000
	dd 0x00000000
ptr3:
	dw 0x03FF
	dd 0x00000000
base_gdt:
	.null:
		times 2 dd 0x00000000
	.code32:
		dw 0xFFFF
		dw 0x0000
		db 0x00
		db 0x9A
		db 0xCF
		db 0x00
	.data32:
		dw 0xFFFF
		dw 0x0000
		dw 0x00
		db 0x92
		db 0xCF
		db 0x00
	.code16:
		dw 0xFFFF
		dw 0x0000
		db 0x00
		db 0x9A
		db 0x0F
		db 0x00
	.data16:
		dw 0xFFFF
		dw 0x0000
		db 0x00
		db 0x92
		db 0x0F
		db 0x00
gdt_ptr:
	dw gdt_ptr - base_gdt - 1
	dd base_gdt
initgui_end:
