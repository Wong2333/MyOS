gcc-4.6 ./main.c -o kernel -c -m32
ld kernel -Ttext 0xc0001500 -e main -o kernel.bin -m elf_i386