..\tool\nasm .\src\mbr.asm -o .\build\mbr.bin -I .\include\  2>  ./compile_output.txt
..\tool\nasm .\src\loader.asm -o .\build\loader.bin -I .\include\  2>>  ./compile_output.txt

