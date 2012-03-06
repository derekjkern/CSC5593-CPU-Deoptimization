#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void eratosthenes( int*, int ) __attribute__((cdecl));

void print_usage() {
	//
	// Use this procedure to let users know the command line format.
	//
	printf( "Invalid arguments to eratosthenes\n" );
	printf( "  Format:  eratosthenes <array size> [print_output?]\n" );
	printf( "  Arguments:\n" );
	printf( "    array_size - Mandatory - The size of the array to find primes in\n" );
	printf( "    print_output? - Optional - Y/N, show the output?\n" );
	printf( "                               Default is N.\n" );
}

int main( int argc, char **argv ) {
    int size_of_array;
    int *prime_array = NULL;
    int print_output = 0;
    int i;

	//
	// If we don't have enough parameters, then let the user know
	//
	if ( argc < 2 ) {
		print_usage();

		exit( 1 );
	}

	//
	// Get the size of the array.  Subtract 1 since the number 1 is
	// not to be considered.
	//
	size_of_array = atoi( argv[1] ) - 1;

	//
	// Allocate the array
	//
	prime_array = (int*) malloc( size_of_array * sizeof( int ) );

	//
	// See if the output should be printed
	//
	if ( argc == 3 ) {
		print_output = ( 'y' == tolower( argv[2][0] ) );
	}

	//
	// Build an array to find primes within.
	//
	for ( i = 0; i < size_of_array; i++ ) {
		prime_array[i] = i + 2;
	}

	//
	// Send the array off to find primes by the assembly code
	//
	eratosthenes( prime_array, size_of_array );

	if ( print_output ) {
		//
		// Print out the prime array.
		//
		printf( "Primes\n" );
		for ( i = 0; i < size_of_array; i++ ) {
			if ( prime_array[i] != 0 ) {
				printf( "%10d", prime_array[i] );
			}
		}
		printf( "\n" );
	}

	//
	// Free the array
	//
	free( prime_array );

    return 0;
}