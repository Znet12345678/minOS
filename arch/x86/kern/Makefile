
NASM=nasm -f elf

all:
	@echo "CC kmain.o"
	@$(CC) -c kmain.c -o kmain.o -nostdlib -I../include -ffreestanding -std=gnu99 -I../fs/zfs -g $(KMAIN_CFLAGS)
	@echo "CC kloader.o"
	@$(CC) -c kloader.c -o kloader.o -nostdlib -I../include -ffreestanding -std=gnu99 -g $(KMAIN_CFLAGS);
	@echo "AS bootloader.o"
	@$(NASM) -f elf bootloader.asm -o bootloader.o -g
	@echo "CC kernel.o"
	@$(CC) -c kernel.c -o kernel.o -nostdlib -I../include -ffreestanding -std=gnu99 -g
	@echo "CC tty.o"
	@$(CC) -c tty.c -o tty.o -nostdlib -I../include -ffreestanding -std=gnu99 -g
	@echo "AS boot.o"
	@$(AS) boot.S -o boot.o -g
	@echo "AS crti.o"
	@$(AS) crti.S -o crti.o  -g
	@echo "AS crtn.o"
	@$(AS) crtn.S -o crtn.o -g
	@echo "AS halt.o"
	@$(AS) halt.S -o halt.o -g
	@echo "NASM inportb.o"
	@echo "CC init.o"
	@$(CC) -c init.c -o init.o -g
	@$(NASM) inportb.asm -o inportb.o -g
	@echo "CC xc.o"
	@$(CC)  -c xw.c -o xw.o -nostdlib -g -I../include -ffreestanding
	@echo "CC panic.o"
	@$(CC) -c panic.c -o panic.o -nostdlib -g  -I../include -ffreestanding
	@echo "AS bootl.o"
	@$(NASM) -f elf bootl.asm -o bootl.o -g
	@echo "CC shell.o"
	@$(CC) -c shell.c -o shell.o -nostdlib -g  -ffreestanding -I../include
	@echo "CC mod.o"
	@$(CC) -c add_module.c -o mod.o -nostdlib -ffreestanding -I../include
clean:
	rm *.o
