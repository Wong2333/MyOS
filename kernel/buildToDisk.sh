./build.sh
dd if=kernel.bin of=../disk.img bs=512 count=200 seek=9 conv=notrunc