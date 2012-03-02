#include <stdio.h>
#include <stdlib.h>

void asm_fib( int*, int ) __attribute__((cdecl));

int main( int argc, char **argv )
{
    int number_of_fibs = atoi( argv[1] );
    int *fibs = (int*) malloc( number_of_fibs * sizeof( int ) );
    int i;

	//
	// Get the fibonacci numbers from the assembly code
	//
	asm_fib( fibs, number_of_fibs );

	//
	// Print out the fibonacci numbers.
	//
	for ( i = 0; i < number_of_fibs; i++ ) {
		printf( "%10d", fibs[i] );
	}
	printf( "\n" );

	free( fibs );

    return 0;
}