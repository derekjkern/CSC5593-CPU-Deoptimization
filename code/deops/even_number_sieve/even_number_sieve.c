#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#if defined(__i386__)
static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}
#elif defined(__x86_64__)
static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}
#endif

void print_usage() {
	//
	// Use this procedure to let users know the command line format.
	//
	printf( "Invalid arguments to even_number_sieve\n" );
	printf( "  Format:  even_number_sieve <array size> <pattern>\n" );
	printf( "  Arguments:\n" );
	printf( "    array_size - Mandatory - The size of the array to sieve\n" );
	printf( "    pattern - Mandatory - The pattern to use when building the array\n" );
	printf( "                          Use 'r' for random and 1 and 2 to specify\n" );
	printf( "                          an odd/even array pattern.  Example #1: 12\n" );
	printf( "                          is an odd followed by an even for the length\n" );
	printf( "                          of the array.  Example #2: r  generates a\n" );
	printf( "                          fully random array.  Example #3: r10  generates\n" );
	printf( "                          a random pattern of length 10 and populates the\n" );
	printf( "                          using it (the pattern is written out)\n" );
	printf( "    print_output? - Optional - Y/N, show the output?\n" );
	printf( "                               Default is N.\n" );
}

int main( int argc, char **argv ) {
    int *number_array = NULL;
    int size_of_array;
    int print_output = 0;
    int i;

	//
	// If we don't have enough parameters, then let the user know
	//
	if ( argc < 3 ) {
		print_usage();

		exit( 1 );
	}

	//
	// See if the output should be printed
	//
	if ( argc == 4 ) {
		print_output = ( argv[3][0] == 'y' || argv[3][0] == 'Y' );
	}

	//
	// Get the size of the array
	//
	size_of_array = atoi( argv[1] );

	//
	// Allocate the array
	//
	number_array = (int*) malloc( size_of_array * sizeof( int ) );

	//
	// Build an array to sieve.
	//
	srand( time( NULL ) );
	if ( strcmp( argv[2], "r" ) == 0 || strcmp( argv[2], "R" ) == 0 ) {
		//
		// Generate a random array
		//
		for ( i = 0; i < size_of_array; i++ ) {
			number_array[i] = ( rand() % 2 ) + 1;
		}
	} else {
		//
		// Set the pattern
		//
		char *pattern = NULL;
		int pattern_length = 0;
		if ( argv[2][0] == 'r' || argv[2][0] == 'R' ) {
			pattern_length = (int) atoi( argv[2] + 1 ) + 1;

			//
			// Allocate the memory for the pattern
			//
            pattern = (char*) malloc( pattern_length * sizeof( char ) );

			//
			// Fill out the pattern
			//
			char buffer[1];
			for( i = 0; i < pattern_length; i++ ) {
				itoa( ( rand() % 2 ) + 1, buffer, 10 );
				pattern[i] = buffer[0];
			}
			pattern[i] = (char) 0;

			//
			// Tell the user about the generated pattern.
			//
			printf( "Auto-generated pattern: %s\n", pattern );
		} else {
			//
			// User manually create the pattern returned it.
			//
			pattern = argv[2];
			pattern_length = strlen( pattern );
		}

		//
		// Generate a patterned array
		//
		int pattern_index = 0;
		for ( i = 0; i < size_of_array; i++ ) {
			number_array[i] = ( pattern[i % pattern_length] == '1' ? 1 : 2 );
		}
	}

	if ( print_output ) {
		//
		// Print out the array prior to sieving.
		//
		printf( "Before\n" );
		for ( i = 0; i < size_of_array; i++ ) {
			printf( "%4d", number_array[i] );
		}
		printf( "\n" );
	}

	//
	// Sieve the array
	//
	unsigned long long pstart = rdtsc();
	for( i = 0; i < size_of_array; i++ ) {
		//
		// If the number is odd, then mark it with a zero
		//
		if ( number_array[i] % 2 == 1 ) {
			number_array[i] = 0;
		}
	}
	printf( "Cycles=%d\n", ( rdtsc() - pstart ) );

	if ( print_output ) {
		//
		// Print out the sieved array.
		//
		printf( "After\n" );
		for ( i = 0; i < size_of_array; i++ ) {
			printf( "%4d", number_array[i] );
		}
		printf( "\n" );
	}

	//
	// Free the array
	//
	free( number_array );

    return 0;
}
