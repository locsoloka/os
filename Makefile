C_SOURCES = $(wildcard src/*.c) $(wildcard src/*/*.c) 
OBJ = boot.o $(C_SOURCES:.c=.o)

CC = gcc
CFLAGS = -m32 -ffreestanding -O2 -Wall -std=gnu99

all: myos.bin

boot.o: boot.asm
	nasm -f elf32 boot.asm -o boot.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

myos.bin: $(OBJ)
	ld -m elf_i386 -T linker.ld -o myos.bin $(OBJ)

run: myos.bin
	qemu-system-i386 -kernel myos.bin

clean:
	rm -f *.o myos.bin