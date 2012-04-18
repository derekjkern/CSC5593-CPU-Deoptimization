    /*////////////////////////////////////////////////////////////////
   //			Load store dependency							   //
  //The main idea is to show the difference the affect of load    //
 //stro dependency& compare it withe the optimized version       //
////////////////////////////////////////////////////////////////*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


////////////////////////////////////////////////////////////////////////
// Send the array off to be counted by the assembly code if it is needed
////////////////////////////////////////////////////////////////////////

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
printf( " Format: Dependency <array size> [print_output?]\n" );
printf( " Arguments:\n" );
printf( " array_size - Mandatory - The size of the array\n" );

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
//			Build a random arry to apply the dependency.
///////////////////////////////////////////////////////

srand( time( NULL ) );
for ( i = 0; i < size_of_array; i++ )
{
load_store_array[i] = ( i % 10 );
}

////////////////////////////////////////////////////////////////
//	De-optimization by loading a value that is stored shortly
///////////////////////////////////////////////////////////////
/*unsigned long long pstart = rdtsc();
for (i=0;i<size_of_array;i++)

{
	load_store_array[i]=load_store_array[i-1]+5;

}
printf( "De-op Cycles=%d\n", ( rdtsc() - pstart ) );
*/
/////////////////////////////////////////////////
//		Initialize the first five Temp
///////////////////////////////////////////////

int temp1=load_store_array[0];
int temp2=load_store_array[1];
int temp3=load_store_array[2];
int temp4=load_store_array[3];
int temp5=load_store_array[4];
int c=5;
unsigned long long pstart = rdtsc();

/*/////////////////////////////////////////////////////////
//The Optimize version by letting the value being stored
//at temorpry variable to be used instead
/////////////////////////////////////////////////////////*/

for (i=0;i<size_of_array;i+=5)

	{
		load_store_array[i]=temp1+c;
		load_store_array[i+1]=temp2+c;
		load_store_array[i+2]=temp3+c;
		load_store_array[i+3]=temp4+c;
		load_store_array[i+4]=temp5+c;

		temp1=load_store_array[i];
		temp2=load_store_array[i+1];
		temp3=load_store_array[i+2];
		temp4=load_store_array[i+3];
		temp5=load_store_array[i+4];

	}
printf( "Cycles=%d\n", ( rdtsc() - pstart ) );



}
