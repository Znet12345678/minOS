//.code16
//cli
//lgdt [gdtr]
//mov eax,cr0
//or al,1
//mov cr0, eax
//JMP 08h:_start
.org 0x8c00
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 
stack_top:
.section .text
.global _start
//.type Start, @function
BOOTSEG = 0x07c0
_start:
	//. = _start + 510
	//.byte 0x55
	//.byte 0xaa
	movl $stack_top, %esp
	call kernel_init
	call _init
	call kernel_main
	cli
	///. = _start + 100000000
	//.byte 0x55
	//.byte 0xaa
.Lhang:
	hlt
	jmp .Lhang
.size _start, . - _start
//.fill (510-(.-_start)),1,0
//BootMagic: .int 0xAA55
