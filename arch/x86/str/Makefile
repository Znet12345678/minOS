
all:
	@echo "CC cmp.o"
	@$(CC) -c cmp.c -o cmp.o -nostdlib -ffreestanding -I../include -g -Werror
	@echo "CC cpy.o"
	@$(CC) -c cpy.c -o cpy.o -nostdlib -ffreestanding -I../include -std=gnu99 -g -Werror
	@echo "CC strlen.o"
	@$(CC) -c strlen.c -o strlen.o -nostdlib -ffreestanding -I../include -g -Werror
clean:
	rm *.o
