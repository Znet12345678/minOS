NASM=nasm
all:
	@echo "CC malloc.o"
	@$(CC) -c malloc.c -o malloc.o -nostdlib -ffreestanding -I../include -std=c99
	@echo "CC mm.o"
	@$(CC) -c mm.c -o mm.o -nostdlib -ffreestanding -I../include -Werror
clean:
	rm *.o
