..\tool\nasm .\mbr.asm -o ..\build\mbr.bin -I .\include\  2>  ./compile_output.txt
..\tool\nasm .\loader.asm -o ..\build\loader.bin -I .\include\  2>>  ./compile_output.txt

