#
# Build the project on Linux - 32bit
#

#
# Build the assembly code
#
nasm -f elf -O0 insertion_sort.asm

#
# Build the C wrapper
#
gcc -m32 -c insertion_sort_main.c

#
# Link the assembly code and C wrapper together
#
gcc -m32 insertion_sort.o insertion_sort_main.o -o insertion_sort

#
# Clean up
#
rm *.o
