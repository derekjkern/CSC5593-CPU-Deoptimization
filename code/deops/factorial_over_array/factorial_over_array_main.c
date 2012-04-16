#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN64
int factorial( int ) __attribute__((cdecl));
#elif _WIN32
int factorial( int ) __attribute__((cdecl));
#elif __linux__
int _factorial( int );
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
	printf( "Invalid arguments to factorial\n" );
	printf( "  Format:  factorial <array size> [print_output?]\n" );
	printf( "  Arguments:\n" );
	printf( "    array_size - Mandatory - The size of the array to factorial\n" );
	printf( "    print_output? - Optional - Y/N, show the output?\n" );
	printf( "                               Default is N.\n" );
}

int main( int argc, char **argv )
{
    int size_of_array;
    unsigned long *factorial_array = NULL;
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
	factorial_array = (unsigned long*) malloc( size_of_array * sizeof( unsigned long ) );

	//
	// See if the output should be printed
	//
	if ( argc == 3 ) {
		print_output = ( 'y' == tolower( argv[2][0] ) );
	}

	//
	// Build an array to factorial.
	//
	srand( time( NULL ) );
	for ( i = 0; i < size_of_array; i++ ) {
		factorial_array[i] = ( rand() % 12 ) + 1;
	}

	if ( print_output ) {
		//
		// Print out the prime array.
		//
		printf( "Before\n" );
		for ( i = 0; i < size_of_array; i++ ) {
			printf( "%10d", factorial_array[i] );
		}
		printf( "\n" );
	}

	//
	// Calculate the factories over the array using the assembly code
	//
	unsigned long long start = rdtsc();
	for ( i = 0; i < size_of_array; i++ ) {
#ifdef _WIN64
		factorial_array[i] = factorial( factorial_array[i] );
#elif _WIN32
		factorial_array[i] = factorial( factorial_array[i] );
#elif __linux__
		factorial_array[i] = _factorial( factorial_array[i] );
#endif
	}
	printf( "Cycles=%d\n", ( rdtsc() - start ) );

	if ( print_output ) {
		//
		// Print out the prime array.
		//
		printf( "After\n" );
		for ( i = 0; i < size_of_array; i++ ) {
			printf( "%10d", factorial_array[i] );
		}
		printf( "\n" );
	}

	//
	// Free the array
	//
	free( factorial_array );

    return 0;
}
