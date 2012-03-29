REM --
REM -- Build the project on Windows - 32bit
REM --

REM --
REM -- Build the assembly code
REM --
yasm -f win32 -O0 mod_ten_counter.asm

REM --
REM -- Build the assembly code
REM --
gcc -c mod_ten_counter_main.c

REM --
REM -- Build the C wrapper
REM --
gcc mod_ten_counter.obj mod_ten_counter_main.o -o mod_ten_counter

REM --
REM -- Clean up
REM --
del *.o
del *.obj