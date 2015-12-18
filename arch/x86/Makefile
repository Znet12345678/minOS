CROSS=i386-elf-
CC=$(CROSS)gcc
CXX=$(CROSS)g++
AS=$(CROSS)as
CFLAGS="-nostdlib -Iinclude -ffreestanding -g"
CXXFLAGS=$(CFLAGS)
LDFLAGS="-nostdlib"
CRTBEG=$(shell $(CC) -print-file-name=crtbegin.o)
CRTEND=$(shell $(CC) -print-file-name=crtend.o)
export CC CXX AS CFLAGS CXXFLLAGS LDFLAGS
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
	@echo "CCLD minOS_kern"
	@$(CROSS)gcc drivers/ata/*.o drivers/PCI/IDE/controller/*.o */*.o fs/broken/zfs/*.o fs/broken/ext2/*.o $(CRTBEG) $(CRTEND) -o minOS_kern   -nostdlib -ffreestanding -T linker.ld
clean:
	make -C kern clean
	make -C io clean
	make -C mem clean
	make -C lib clean
	make -C drivers clean
	make -C str clean
