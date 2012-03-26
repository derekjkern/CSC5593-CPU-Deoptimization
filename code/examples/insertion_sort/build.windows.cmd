REM --
REM -- Build the project on Windows - 32bit
REM --

REM --
REM -- Build the assembly code
REM --
yasm -f win32 -O0 insertion_sort.asm

REM --
REM -- Build the assembly code
REM --
gcc -c insertion_sort_main.c

REM --
REM -- Build the C wrapper
REM --
gcc insertion_sort.obj insertion_sort_main.o -o insertion_sort

REM --
REM -- Clean up
REM --
del *.o
del *.obj