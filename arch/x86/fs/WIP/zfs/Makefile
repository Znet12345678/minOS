all:
	@echo "CC zfs.o"
	@$(CC) -c zfs.c -o zfs.o -nostdlib -ffreestanding -I../../../include -std=gnu99
	@echo "CC mkfs.zfs.c"
	@gcc mkfs.zfs.c -o mkfs.zfs -std=c99
