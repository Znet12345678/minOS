//.code16
.section .init
.global _init
.type _init, @function
_init:
	push %ebp
	movl %esp, %ebp

.section .fini
.global _fini
.type _fini, @function
_fini:
	push %ebp
	movl %esp, %ebp
	. = _fini + 510
	//times 510-($-$$) .byte 0x00
	.fill(510-(.-main)),1,0
	.byte 0x55
	.byte 0xaa
.section .sig
.global _sig
_sig:
	.fill (510-(.-main)),1,0
	.int 0xAA55
	//.byte 0x55
	//.byte 0xaa
