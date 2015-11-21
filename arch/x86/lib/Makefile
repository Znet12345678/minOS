all:
	@echo "CC panic.o"
	@$(CC) -c panic.c -o panic.o -nostdlib -DDEV -g
	@echo "CC sleep.o"
	@$(CC) -c sleep.c -o sleep.o -nostdlib -ffreestanding -g -std=gnu99
	@echo "CC atox.o"
	@$(CC) -c atox.c -o atox.o -nostdlib -I../include -g 
clean:
	rm *.o

