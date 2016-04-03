CROSS=i386-elf-
CC=$(CROSS)gcc
CXX=$(CROSS)g++
AS=$(CROSS)as

CFLAGS="-nostdlib -Iinclude -ffreestanding -g"
CXXFLAGS=$(CFLAGS)
KMAIN_CFLAGS="-DRELEASE"
LDFLAGS="-nostdlib"
CRTBEG=$(shell $(CC) -print-file-name=crtbegin.o)
CRTEND=$(shell $(CC) -print-file-name=crtend.o)
export CC CXX AS CFLAGS CXXFLLAGS LDFLAGS KMAIN_CFLAGS
all:
	@make -C kern
	@make -C io
	@make -C mem
	@make -C lib
	@make -C str
	@make -C drivers
	@make -C fs
	@make -C gui
	@make -C exec/elf
#	@echo "CC "
#	@86_64-elf-gcc -c bootstrap.S -o  
	@echo "CCLD kernel.elf"
	@$(CROSS)gcc ./kern/chainload.o ./kern/jmp.o ./exec/elf/elf.o ./mem/malloc.o ./drivers/ata/ata.o ./drivers/PCI/IDE/controller/pci_ide_controller.o ./str/cpy.o ./str/strlen.o ./str/cmp.o ./io/io.o ./io/inportsl.o ./io/kprintf.o ./fs/broken/zfs/zfs.o ./fs/broken/ext2/ext2.o ./fs/WIP/zfs/zfs.o ./fs/WIP/fs/fs.o ./fs/WIP/fat/fat32.o ./fs/WIP/minfs/minfs.o ./lib/panic.o ./lib/atox.o ./lib/sleep.o  ./kern/xw.o ./kern/initgui.o ./kern/panic.o ./kern/crti.o ./kern/tty.o ./kern/reboot.o ./kern/kmain.o ./kern/rm.o ./kern/boot.o ./kern/int32.o ./kern/kloader.o ./kern/shell.o ./kern/halt.o ./kern/kernel.o ./kern/mod.o ./kern/crtn.o ./kern/bootl.o ./kern/init.o  ./kern/inportb.o  ./gui/libgui.o $(CRTBEGIN) $(CRTEND) -o kernel.elf -nostdlib -T linker.ld 
#	#@$(CROSS)gcc io/inportsl.o io/io.o drivers/ata/ata.o drivers/PCI/IDE/controller/*.o  fs/broken/*/*.o fs/WIP/*/*.o lib/panic.o lib/atox.o  mem/malloc.o ./kern/int32.o ./kern/kloader.o ./kern/shell.o ./kern/halt.o ./kern/kernel.o ./kern/mod.o ./kern/crtn.o ./kern/bootl.o ./kern/init.o ./kern/inportb.o ./gui/libgui.o ./lib/sleep.o ./kern/xw.o ./kern/initgui.o ./kern/panic.o ./kern/crti.o ./kern/tty.o ./kern/reboot.o ./kern/kmain.o ./kern/rm.o ./kern/boot.o io/kprintf.o str/cmp.o str/cpy.o str/strlen.o $(CRTBEGIN) $(CRTEND) -o kernel.elf -nostdlib -T linker.ld -ffreestanding
#	#@$(CROSS)gcc 
#	@$(CROSS)gcc fs/WIP/minfs/*.o drivers/ata/*.o drivers/PCI/IDE/controller/*.o */*.o fs/broken/zfs/*.o fs/broken/ext2/*.o fs/WIP/fat/*.o $(CRTBEG) $(CRTEND) -o kernel.elf -nostdlib -ffreestanding -T linker.ld
#	@echo "Ignore this,for it is broken. I just set up some things for much later on."	
##	@echo "Building boot image:booti"
#	@echo "Initialising file:bootloader.hw.S"
#	@echo ".section .bindata" > bootloader.hw.S
#	@echo ".incbin \"kern/bootloader.bin\"" >> bootloader.hw.S
#	@echo "CCLD booti"
#	$(CC) -T booti.lsh bootloader.hw.S gui/*.o fs/WIP/minfs/*.o drivers/ata/*.o drivers/PCI/IDE/controller/*.o */*.o fs/broken/zfs/*.o fs/broken/ext2/*.o $(CRTBEG) $(CRTEND) -o booti -nostdlib
	if [ -a libkern.elf.a ] ;	then \
		 rm libkern.elf.a;fi
	cp kern/bootloader.bin booti
	cat micros_kern >> booti
	@make -C utils
	@echo "Building libkern.so.elf"
	@echo "CC lib/panic.libo"
	@$(CC) -c lib/panic.c -o lib/panic.libo -D__LIB_BUILD -Iinclude
	@echo "CC kern/shell.libo"
	@$(CC) -c kern/shell.c -o kern/shell.libo -D__LIB_BUILD -Iinclude -std=c99
	@echo "CC kern/panic.libo"
	@$(CC) -c kern/panic.c -o kern/panic.libo -D__LIB_BUILD -Iinclude -std=c99 
#	#@echo "LD libkern.a"
	$(CROSS)ar rcs libkern.a io/kprintf.o kern/inportb.o lib/sleep.o kern/kernel.o  kern/init.o fs/WIP/minfs/*.o drivers/ata/*.o drivers/PCI/IDE/controller/*.o str/*.o mem/*.o io/*.o fs/broken/zfs/*.o fs/broken/ext2/*.o fs/WIP/fat/*.o $(CRTBEG) $(CRTEND) gui/*.o lib/panic.libo   kern/reboot.o kern/tty.o kern/panic.libo   kern/shell.libo kern/int32.o kern/halt.o kern/yourboot.o kern/mod.o
	@echo "LD yourkernel.elf"
	@$(CC) kern/yourkernel.o kern/crti.o kern/crtn.o $(CRTBEGIN) $(CRTEND) -o yourkernel.elf -nostdlib -L. -lkern -T linker.ld
clean:
	make -C kern clean
	make -C io clean
	make -C mem clean
	make -C lib clean
	make -C drivers clean
	make -C str clean
