# makefile for square.asm
task: main.c input.o inrnd.o output.o square.o
	gcc -g -o task main.c input.o inrnd.o output.o square.o -no-pie
input.o: input.asm
	nasm -f elf64 -g -F dwarf input.asm -l input.lst
inrnd.o: inrnd.asm
	nasm -f elf64 -g -F dwarf inrnd.asm -l inrnd.lst
output.o: output.asm
	nasm -f elf64 -g -F dwarf output.asm -l output.lst
square.o: square.asm
	nasm -f elf64 -g -F dwarf square.asm -l square.lst
