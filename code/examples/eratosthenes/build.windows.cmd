REM --
REM -- Build the project on Windows - 32bit
REM --

REM --
REM -- Build the assembly code
REM --
yasm -f win32 -O0 --list=eratosthenes.lst eratosthenes.asm

REM --
REM -- Build the C wrapper
REM --
gcc -c eratosthenes_main.c

REM --
REM -- Link the assembly code and C wrapper together
REM --
gcc eratosthenes.obj eratosthenes_main.o -o eratosthenes

REM --
REM -- Clean up
REM --
del *.o
del *.obj