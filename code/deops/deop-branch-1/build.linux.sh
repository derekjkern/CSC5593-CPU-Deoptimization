#
# Build the project on Linux - 32bit
#

#
# Build the assembly code
#
nasm -f elf -O0 mod_ten_counter.asm

#
# Build the C wrapper
#
gcc -m32 -c mod_ten_counter_main.c

#
# Link the assembly code and C wrapper together
#
gcc -m32 mod_ten_counter.o mod_ten_counter_main.o -o mod_ten_counter

#
# Clean up
#
rm *.o
