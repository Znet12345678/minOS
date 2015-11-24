ENTRY(_start)

SECTIONS
{
	. = 0x7c00;
	.text BLOCK(4K) : ALIGN(4K){
		*(.multiboot)
		*(.text)
	}
	.rodata BLOCK(4K) : ALIGN(4K){
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K){
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	
}

