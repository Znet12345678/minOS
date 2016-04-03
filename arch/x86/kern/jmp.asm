global jmp_boot
jmp_boot:
	JMP 0x00100000
hang:
	JMP hang
