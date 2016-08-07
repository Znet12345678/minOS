all:
	nasm -f bin bootloader.asm -o bootloader.bin
	nasm -f bin hd.asm -o hd.img
	nasm -f bin itworks.asm -o itworks.bin
	nasm -f bin stage2.asm -o stage2.bin
	cc -c makefloppy.c -o makefloppy.o -std=gnu99 -fmax-errors=1
	cc makefloppy.o -o makefloppy
	nasm -f bin nboot.asm -o nbootloader.bin
