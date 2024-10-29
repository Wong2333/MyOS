./build.sh
dd if=./build/mbr of=../hd60M.img bs=512 count=1 conv=notrunc
dd if=./build/loader of=../hd60M.img seek=2 bs=512 count=4 conv=notrunc