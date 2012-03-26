#
# Build the project on Linux - 32bit
#

#
# Build the assembly code
#
nasm -f elf -O0 eratosthenes.asm

#
# Build the C wrapper
#
gcc -m32 -c eratosthenes_main.c

#
# Link the assembly code and C wrapper together
#
gcc -m32 eratosthenes.o eratosthenes_main.o -o eratosthenes

#
# Clean up
#
rm *.o
