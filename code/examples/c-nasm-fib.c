#include <stdio.h>

int fib(int) __attribute__((cdecl));

int main( int argc, char **argv )
{
    int fib_of_integer = atoi( argv[1] );

    fib( fib_of_integer );

    return 0;
}