#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
	printf( "Invalid arguments to div_vs_mult_op\n" );
	printf( "  Format:  factorial <array size> [print_output?]\n" );
	printf( "  Arguments:\n" );
	printf( "    array_size - Mandatory - The size of the array to float test\n" );
}

int main( int argc, char **argv )
{
    int size_of_array;
    unsigned long *test_array = NULL;
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
	test_array = (unsigned long*) malloc( size_of_array * sizeof( unsigned long ) );

	//
	// Build an array to work on.
	//
	srand( time( NULL ) );
	for ( i = 0; i < size_of_array; i++ ) {
		test_array[i] = (unsigned long) pow( 2, ( rand() % 12 ) );
	}

	//
	// Calculate over the array
	//
	unsigned long long start = rdtsc();
	for ( i = 0; i < size_of_array; i++ ) {
		test_array[i] = test_array[i] * 0.5;
	}
	printf( "Cycles=%d\n", ( rdtsc() - start ) );

	//
	// Free the array
	//
	free( test_array );

    return 0;
}
