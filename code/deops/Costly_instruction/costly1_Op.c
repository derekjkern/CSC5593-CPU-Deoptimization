  /*////////////////////////////////////////////////////////////////
 				More costly instruction_Random
/////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


///////////////////////////////////////////////////////////////////
// Send the array off to be counted by the assembly code if it needs
///////////////////////////////////////////////////////////////////
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

  //////////////////////////////////////////////////////////////////
 // Use this procedure to let users know the command line format.//
//////////////////////////////////////////////////////////////////

void print_usage() {
printf( "Invalid arguments to insertion_sort\n" );
printf( " Format: More_costly_instruction <array size> \n" );
printf( " Arguments:\n" );
printf( " array_size - Mandatory - The size of the array to be divided\n" );
}



////////////////////////////////////////////////////////////////


int main( int argc, char **argv ) 
{
    int *load_store_array = NULL;
    int size_of_array;
    int print_output = 0;
    int i;


	if ( argc < 2 )    //to check the validity of the argument
	{
	print_usage();

	exit( 1 );
	}


 /////////////////////////////////////////////////////// 
//Get the size of the array    THEN    Allocate it
///////////////////////////////////////////////////////

size_of_array = atoi( argv[1] );

load_store_array = (int*) malloc( size_of_array * sizeof( int ) );


////////////////////////////////////////////////////////
//			Build an array to sort.
///////////////////////////////////////////////////////

srand( time( NULL ) );
for ( i = 0; i < size_of_array; i++ )
{
load_store_array[i] = ( i % 10 +1 );
}

int result;
//int A=1000;
int B=100;
int C=10;
unsigned long long pstart = rdtsc();

/*/////////////////////////////////////////////////////////////
				The De-optimization technique
				  By using three divisions 
////////////////////////////////////////////////////////////*/
/*
for (i=0;i<size_of_array;i++)

{
	result=load_store_array[i]/B/C;
}

printf( "De-op Cycles=%d\n", ( rdtsc() - pstart ) );

*/
/*/////////////////////////////////////////////////////////////
			 The Optimization technique
		By using muliplication istead of division
////////////////////////////////////////////////////////////*/

pstart = rdtsc();

for (i=0;i<size_of_array;i++)

{

		result=load_store_array[i]/(B*C);
}

printf( "Cycles=%d\n", ( rdtsc() - pstart ) );


}
