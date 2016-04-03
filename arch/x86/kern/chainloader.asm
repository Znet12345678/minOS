[bits 32]
section .text
global chainload
%define RM_BASE                             0x7C00
%define REBASE(x)                              (((x) - reloc) + RM_BASE)
%define GDTENTRY(x)                            ((x) &lt;< 3)
%define CODE32                                 GDTENTRY(1)  ; 0x08
%define DATA32                                 GDTENTRY(2)  ; 0x10
%define CODE16                                 GDTENTRY(3)  ; 0x18
%define DATA16                                 GDTENTRY(4)  ; 0x20
%define STACK16                                (RM_BASE)
chainload:
	JMP 0x18:go_real
go_real:use16
	cli
	mov eax,cr0
	and al,~0x01
	mov cr0,eax
	sti
	JMP 0x00100000
_chainload:cli
	pusha
	mov esi,reloc
	mov edi,RM_BASE
	mov ecx,(end - reloc)
	cld
	rep movsb
;	JMP chainload
	JMP word RM_BASE
reloc:use32
	;jmp reloc
	mov [REBASE(stack32_pntr)],esp
	sidt [REBASE(idt32_pntr)]
	sgdt [REBASE(gdt32_pntr)]
	lgdt [REBASE(gdt_ptr)]
	lea  esi, [esp+0x24]
	lodsd
;	jmp reloc
;	mov [0],al
	mov esi,[esi]
	mov edi,STACK16
	mov ecx,0
;	jmp reloc
	rep  movsb
;	jmp reloc
	jmp  word pmode_16
pmode_16:use16
	mov eax,cr0
	and al,~0x01
	mov cr0,eax
	jmp  word 0x0000:REBASE(rmode_16)
rmode_16:
	JMP 0x00100000


stack32_pntr:
	dd 0x00000000
idt32_pntr:
	dw 0x0000
	dd 0x00000000
gdt32_pntr:
        dw 0x0000
        dd 0x00000000
idt16_pntr:
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

end:
