build.bat
..\tool\dd if=.\build\mbr.bin of=..\disk.img bs=512 count=1
..\tool\dd if=.\build\loader.bin of=..\disk.img seek=2 bs=512 count=4