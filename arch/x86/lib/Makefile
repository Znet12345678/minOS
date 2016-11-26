all:
	@echo "CC panic.o"
	@$(CC) -c panic.c -o panic.o -nostdlib -DDEV -g -DNOPANIC -Werror -I../include -ffreestanding
	@echo "CC sleep.o"
	@$(CC) -c sleep.c -o sleep.o -nostdlib -ffreestanding -g -std=gnu99 -Werror -I../include 
	@echo "CC atox.o"
	@$(CC) -c atox.c -o atox.o -nostdlib -I../include -g -Werror
#	@echo "CC io.o"
#	@$(CC) -c io.c -o io.o -nostdlib -I../include -ffreestanding
clean:
	rm *.o

