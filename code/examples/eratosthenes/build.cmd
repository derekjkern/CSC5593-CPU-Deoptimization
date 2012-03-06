yasm -f win32 -O0 --list=eratosthenes.lst eratosthenes.asm

gcc -c eratosthenes_main.c

gcc eratosthenes.obj eratosthenes_main.o -o eratosthenes
