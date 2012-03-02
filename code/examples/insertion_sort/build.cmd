yasm -f win32 -O0 insertion_sort.asm

gcc -c insertion_sort_main.c

gcc insertion_sort.obj insertion_sort_main.o -o insertion_sort
