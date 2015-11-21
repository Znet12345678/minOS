.section .text
.code32

multiboot_header:
   
bs:
	call kernel_loader_init
	call _init
	call kernel_loader_main
