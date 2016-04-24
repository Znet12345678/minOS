
all:
	@echo "CC malloc.o"
	@$(CC) -c malloc.c -o malloc.o -nostdlib -ffreestanding
	@echo "CC mm.o"
	@$(CC) -c mm.c -o mm.o -nostdlib -ffreestanding -I../include -Werror
clean:
	rm *.o
