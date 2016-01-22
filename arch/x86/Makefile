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
	@echo "CC bootstrap.o"
#	@x86_64-elf-gcc -c bootstrap.S -o bootstrap.o 
	@echo "CCLD micros_kern"
	@$(CROSS)gcc fs/WIP/minfs/*.o drivers/ata/*.o drivers/PCI/IDE/controller/*.o */*.o fs/broken/zfs/*.o fs/broken/ext2/*.o fs/WIP/fat/*.o $(CRTBEG) $(CRTEND) -o micros_kern   -nostdlib -ffreestanding -T linker.ld
	@echo "Ignore this,for it is broken. I just set up some things for much later on."	
	@echo "Building boot image:booti"
#	@echo "Initialising file:bootloader.hw.S"
#	@echo ".section .bindata" > bootloader.hw.S
#	@echo ".incbin \"kern/bootloader.bin\"" >> bootloader.hw.S
#	@echo "CCLD booti"
#	$(CC) -T booti.lsh bootloader.hw.S fs/WIP/minfs/*.o drivers/ata/*.o drivers/PCI/IDE/controller/*.o */*.o fs/broken/zfs/*.o fs/broken/ext2/*.o $(CRTBEG) $(CRTEND) -o booti -nostdlib
	if [ -a booti ] ;	then \
		 rm booti;fi
	cp kern/bootloader.bin booti
	cat micros_kern >> booti
clean:
	make -C kern clean
	make -C io clean
	make -C mem clean
	make -C lib clean
	make -C drivers clean
	make -C str clean
