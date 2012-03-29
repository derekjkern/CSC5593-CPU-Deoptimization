#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN64
void mod_ten_counter( int*, int*, int ) __attribute__((cdecl));
#elif _WIN32
void mod_ten_counter( int*, int*, int ) __attribute__((cdecl));
#elif __linux__
void _mod_ten_counter( int*, int*, int );
#endif

void print_usage() {
	//
	// Use this procedure to let users know the command line format.
	//
	printf( "Invalid arguments to mod_ten_counter\n" );
	printf( "  Format:  mod_ten_counter <array size>\n" );
	printf( "  Arguments:\n" );
	printf( "    array_size - Mandatory - The size of the array to count\n" );
}

int main( int argc, char **argv ) {
    int *mod_ten_array = NULL;
    int counts[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int size_of_array;
    int i;

	//
	// If we don't have enough parameters, then let the user know
	//
	if ( argc < 2 ) {
		print_usage();

		exit( 1 );
	}

	//
	// Get the size of the array
	//
	size_of_array = atoi( argv[1] );

	//
	// Allocate the array
	//
	mod_ten_array = (int*) malloc( size_of_array * sizeof( int ) );

	//
	// Build an array to sort.
	//
	srand( time( NULL ) );
	for ( i = 0; i < size_of_array; i++ ) {
		mod_ten_array[i] = rand() % 10;
	}

	//
	// Send the array off to be sorted by the assembly code
	//
#ifdef _WIN64
	mod_ten_counter( counts, mod_ten_array, size_of_array );
#elif _WIN32
	mod_ten_counter( counts, mod_ten_array, size_of_array );
#elif __linux__
	_mod_ten_counter( counts, mod_ten_array, size_of_array );
#endif

	//
	// Print out the count array.
	//
	for ( i = 0; i < 10; i++ ) {
		printf( "'%d' = %d\n", i, counts[i] );
	}

	//
	// Free the array
	//
	free( mod_ten_array );

    return 0;
}
