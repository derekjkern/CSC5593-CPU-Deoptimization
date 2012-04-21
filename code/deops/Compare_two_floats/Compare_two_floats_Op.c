#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define FLOAT2INTCAST(f) (*((int *)(&f)))
#define FLOAT2UINTCAST(f) (*((unsigned int *)(&f)))
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
printf( " Format: insertion_sort <nuberof iteration> [print_output?]\n" );
printf( " Arguments:\n" );
printf( " # of iteration - Mandatory - the number of iterations\n" );
}

	int sum;
	// This function is chosed to be as simple as possilbe 
	//we need to have function call only doesn't matter how complex this function is
	
	int Count_numbers( int a)

	{
		sum+=a;
	}

	
///////////////////////////////////////////////////////////////
int main( int argc, char **argv ) 
{
	/*public int count=0;
	public int b;*/
	unsigned int i,j,k;
    int numberof_iteration;
    int print_output = 0;
	unsigned long long pstart = rdtsc();
	unsigned long long result, result1, result2,result3;
	char c;
	numberof_iteration = atoi( argv[1] );

	int count=0;
	float f1=1.0;
	float f2=0.10;
	float f3=10.5;
	float f4=5.5;


	if ( argc < 2 )    //to check the validity of the argument
	{
	print_usage();

	exit( 1 );
	}

	float t=f1-f2;
	void check_time()
	{
		
	for (j = 0; j <numberof_iteration ; j++)
		{
								//Less costly condition
									
			if (FLOAT2INTCAST(t)<=0)
				{
												
					Count_numbers(i);
					count++;
			        }
			else
					count++;
		}
	result1=rdtsc()-pstart;
	printf( "Cycles=%d\n",result1 );						
}


	check_time();

	



}
