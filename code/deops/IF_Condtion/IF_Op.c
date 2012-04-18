/* More_costly_IF: the main idea is to show how small change could have a big affect
on the number of cycles*/
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
printf( "Invalid arguments to More_costly_IF\n" );
printf( " Format: IF <nuberof iteration> \n" );
printf( " Arguments:\n" );
printf( " Number of iteration - Mandatory \n" );
}
///////////////////////////////////////////////////////////////////



	int sum;
	
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

	if ( argc < 2 )    //to check the validity of the argument
	{
	print_usage();

	exit( 1 );
	}

	
	void check_time()
	{
		/*
								pstart = rdtsc();
								for (i = 0; i <numberof_iteration ; i++)
									{
										//less possible condition first
										if (count==8 || count<numberof_iteration )
											{
												
												Count_numbers(i);
												count++;
										    }
										else
											count++;
										
									}	
							
								result=rdtsc()-pstart;
								printf( "Cycles=%d\n", result );
				*/
								pstart = rdtsc();
	
								for (j = 0; j <numberof_iteration ; j++)
									{
										//more possible scenario first
										if (count<numberof_iteration||count==8)
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
