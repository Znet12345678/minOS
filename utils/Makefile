CC=gcc
all:
	@echo "CC mkfs.minfs.o"
	@$(CC) -c ../arch/x86/fs/WIP/minfs/mkfs.minfs.c -o mkfs.minfs.o
	@echo "LD mkfs.minfs"
	@$(CC) mkfs.minfs.o -o mkfs.minfs 
clean:
	@echo "RM mkfs.minfs.o"
	@rm mkfs.minfs.o
	@echo "RM mkfs.minfs"
	@rm mkfs.minfs
