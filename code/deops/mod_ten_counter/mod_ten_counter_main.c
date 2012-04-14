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
	printf( "Invalid arguments to mod_ten_counter\n" );
	printf( "  Format:  mod_ten_counter <array size>\n" );
	printf( "  Arguments:\n" );
	printf( "    array_size - Mandatory - The size of the array to count\n" );
	printf( "    print_output? - Optional - Y/N, show the output?\n" );
	printf( "                               Default is N.\n" );
}

int main( int argc, char **argv ) {
    int *mod_ten_array = NULL;
    int counts[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int size_of_array;
    int print_output = 0;
    int i;

	//
	// If we don't have enough parameters, then let the user know
	//
	if ( argc < 2 ) {
		print_usage();

		exit( 1 );
	}

	if ( argc == 3 ) {
		print_output = ( 'y' == tolower( argv[2][0] ) );
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
		mod_ten_array[i] = ( i % 10 );
	}

	//
	// Send the array off to be counted by the assembly code
	//
	unsigned long long start = rdtsc();
#ifdef _WIN64
	mod_ten_counter( counts, mod_ten_array, size_of_array );
#elif _WIN32
	mod_ten_counter( counts, mod_ten_array, size_of_array );
#elif __linux__
	_mod_ten_counter( counts, mod_ten_array, size_of_array );
#endif
	printf( "Cycles=%d\n", ( rdtsc() - start ) );

	if ( print_output ) {
		//
		// Print out the count array.
		//
		printf( "\n" );
		for ( i = 0; i < 10; i++ ) {
			printf( "'%d' = %d\n", i, counts[i] );
		}
	}

	//
	// Free the array
	//
	free( mod_ten_array );

    return 0;
}
