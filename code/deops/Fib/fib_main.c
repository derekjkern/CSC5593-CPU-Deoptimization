#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN64
void asm_agi( int*,int ) __attribute__((cdecl));
#elif _WIN32
void asm_agi( int*, int ) __attribute__((cdecl));
#elif __linux__
void asm_agi( int*, int );
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

int main( int argc, char **argv )
{
    int number_of_fibs = atoi( argv[1] );
    int *fibs = (int*) malloc( number_of_fibs * sizeof( int ) );
    int i;

//
// Get the fibonacci numbers from the assembly code
//
unsigned long long start = rdtsc();
#ifdef _WIN64
asm_agi( fibs, number_of_fibs );
#elif _WIN32
asm_agi( fibs, number_of_fibs );
#elif __linux__
_asm_agi( fibs, number_of_fibs );
#endif

printf( "Cycles=%d\n", ( rdtsc() - start ) );

//
// Print out the fibonacci numbers.
//
for ( i = 0; i < number_of_fibs; i++ ) {
printf( "%10d", fibs[i] );
}
printf( "\n" );

free( fibs );

    return 0;
}
