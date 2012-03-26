#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN64
void insertion_sort( int*, int ) __attribute__((cdecl));
#elif _WIN32
void insertion_sort( int*, int ) __attribute__((cdecl));
#elif __linux__
void _insertion_sort( int*, int );
#endif

void print_usage() {
	//
	// Use this procedure to let users know the command line format.
	//
	printf( "Invalid arguments to insertion_sort\n" );
	printf( "  Format:  insertion_sort <array size> [print_output?]\n" );
	printf( "  Arguments:\n" );
	printf( "    array_size - Mandatory - The size of the array to sort\n" );
	printf( "    print_output? - Optional - Y/N, show the output?\n" );
	printf( "                               Default is N.\n" );
}

int main( int argc, char **argv ) {
    int size_of_array;
    int max_array_value;
    int *sorting_array = NULL;
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
	// Get the size of the array
	//
	size_of_array = atoi( argv[1] );

	//
	// Set the maximum element size to be 100 times the array size.
	//
	max_array_value = size_of_array * 100;

	//
	// Allocate the array
	//
	sorting_array = (int*) malloc( size_of_array * sizeof( int ) );

	//
	// See if the output should be printed
	//
	if ( argc == 3 ) {
		print_output = ( 'y' == tolower( argv[2][0] ) );
	}

	//
	// Build an array to sort.
	//
	srand( time( NULL ) );
	for ( i = 0; i < size_of_array; i++ ) {
		sorting_array[i] = rand() % max_array_value;
	}

	if ( print_output ) {
		//
		// Print out the array prior to sorting.
		//
		printf( "Before\n" );
		for ( i = 0; i < size_of_array; i++ ) {
			printf( "%10d", sorting_array[i] );
		}
		printf( "\n" );
	}

	//
	// Send the array off to be sorted by the assembly code
	//
#ifdef _WIN64
	insertion_sort( sorting_array, size_of_array );
#elif _WIN32
	insertion_sort( sorting_array, size_of_array );
#elif __linux__
	_insertion_sort( sorting_array, size_of_array );
#endif

	if ( print_output ) {
		//
		// Print out the sorted array.
		//
		printf( "After\n" );
		for ( i = 0; i < size_of_array; i++ ) {
			printf( "%10d", sorting_array[i] );
		}
		printf( "\n" );
	}

	//
	// Free the array
	//
	free( sorting_array );

    return 0;
}
