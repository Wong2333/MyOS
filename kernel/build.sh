nasm -o ../lib/kernel/print.o -f elf ../lib/kernel/print.s

gcc-4.6 ./main.c -o kernel -c -m32 -I ../lib/kernel
ld -o kernel.bin -m elf_i386 -Ttext 0xc0001500 -e main kernel ../lib/kernel/print.o