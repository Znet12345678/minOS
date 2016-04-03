section .text
global go_real
%define RM_BASE                             0x7C00
%define REBASE(x)                              (((x) - reloc) + RM_BASE)
%define GDTENTRY(x)                            ((x) &lt;< 3)
%define CODE32                                 GDTENTRY(1)  ; 0x08
%define DATA32                                 GDTENTRY(2)  ; 0x10
%define CODE16                                 GDTENTRY(3)  ; 0x18
%define DATA16                                 GDTENTRY(4)  ; 0x20
%define STACK16                                (RM_BASE)
extern _int32,int32_reloc
go_real:use32
___go_real:
	;JMP _int32
	;JMP int32_reloc
        mov [REBASE(stack32_pntr)],esp
        sidt [REBASE(idt32_pntr)]
        sgdt [REBASE(gdt32_pntr)]
        lgdt [REBASE(base_gdt)]
        lea  esi, [esp+0x24]
        lodsd
;       mov [REBASE(ib)],al
        mov esi,[esi]
        mov edi,STACK16
        mov ecx,0
        rep  movsb
        jmp  word 0x18:REBASE(pmode_16)

	JMP 0x18:REBASE(__go_real)
__go_real:cli
	use16
	mov eax,cr0
	and al,~0x01
	mov cr0,eax
	sti
_go_real:cli
	pusha
	mov esi,reloc
	mov edi,RM_BASE
	mov ecx,(end)
	cld
	rep movsb
	JMP 0x7C000
reloc:use32
	mov [REBASE(stack32_pntr)],esp
	sidt [REBASE(idt32_pntr)]
	sgdt [REBASE(gdt32_pntr)]
	lgdt [REBASE(base_gdt)]
	lea  esi, [esp+0x24]
	lodsd
;	mov [REBASE(ib)],al
	mov esi,[esi]
	mov edi,STACK16
	mov ecx,0
	rep  movsb
	jmp  word 0x18:REBASE(pmode_16)
pmode_16:use16
	mov eax,cr0
	and al,~0x01
	mov cr0,eax
	jmp  word 0x0000:REBASE(rmode_16)  
rmode_16:
	
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
