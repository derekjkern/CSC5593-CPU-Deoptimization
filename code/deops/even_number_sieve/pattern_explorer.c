#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN64
	#include <process.h>
#elif _WIN32
	#include <process.h>
#elif __linux__
	#include <unistd.h>
#endif

#define MAX_PATTERN_SIZE	402
#define TEST_ITERATIONS		10
#define MAX_BEST_PATTERNS	10

void print_usage() {
	//
	// Use this procedure to let users know the command line format.
	//
	printf( "Invalid arguments to pattern_explorer\n" );
	printf( "  Format:  pattern_explorer <exe_name> <array_size>\n" );
	printf( "  Arguments:\n" );
	printf( "    exe_name - Mandatory - The executable name of the pattern\n" );
	printf( "                           analyzer\n" );
	printf( "    array_size - Mandatory - The size of the array to sieve\n" );
	printf( "    search_iterations - Mandatory - The number of iterations to\n" );
	printf( "                                    to try when searching\n" );
}

int main( int argc, char **argv ) {
	FILE *executable_output;
	char base_executable_run_command[100], executable_run_command[MAX_PATTERN_SIZE + 100], output_buffer[500];
	char current_pattern[MAX_PATTERN_SIZE], best_patterns[MAX_BEST_PATTERNS][MAX_PATTERN_SIZE];
	unsigned long reasonable_cycles, total_cycles, current_cycles, best_averages[MAX_BEST_PATTERNS];
	int search_count, search_iterations, test_count, test_iterations = TEST_ITERATIONS;
	int i = 0, pattern_length = 0;
	int smallest_index = 0;
	unsigned long smallest_average = 0, current_average;

	//
	// If we don't have enough parameters, then let the user know
	//
	if ( argc < 4 ) {
		print_usage();

		exit( 1 );
	}

	//
	// Get the executable name, the size of the array and the
	// number of search iterations
	//
	sprintf( base_executable_run_command, "%s %s", argv[1], argv[2] );
	search_iterations = atoi( argv[3] );

	//
	// Clear best averages
	//
	for( i = 0; i < MAX_BEST_PATTERNS; i++ ) {
		best_averages[i] = 0;
	}

	//
	// Now, search for good patterns over a certain number of iterations.
	//
	for( search_count = 0; search_count < search_iterations; search_count++ ) {
		//
		// Generate a new pattern.  Start by fixing a pattern length
		//
		pattern_length = ( rand() % ( MAX_PATTERN_SIZE - 2 ) ) + 2;

		//
		// Clear the memory for the pattern and the command.
		//
		memset( current_pattern, 0, MAX_PATTERN_SIZE );
		memset( executable_run_command, 0, MAX_PATTERN_SIZE + 100 );

		//
		// Fill out the pattern
		//
		char buffer[1];
		for( i = 0; i < pattern_length; i++ ) {
			itoa( ( rand() % 2 ) + 1, buffer, 10 );
			current_pattern[i] = buffer[0];
		}
		current_pattern[i] = (char) 0;

		//
		// Finally, fix the command.
		//
		sprintf( executable_run_command, "%s %s", base_executable_run_command, current_pattern );

		total_cycles = 0;
		reasonable_cycles = 0;
		for( test_count = 0; test_count < test_iterations; test_count++ ) {
			//
			// Run the executable and capture the output.
			//
			executable_output = popen( executable_run_command, "r" );

			//
			// Read the cycles for this run and add them to the total.
			//
			fgets( output_buffer, 500, executable_output );
			fgets( output_buffer, 500, executable_output );
			sscanf( output_buffer, "Cycles=%lu\n", &current_cycles );

			//
			// Try to discard bad results.
			//
			if ( reasonable_cycles == 0 || current_cycles < reasonable_cycles ) {
				reasonable_cycles = current_cycles * 1.5;
				total_cycles += current_cycles;
			} else {
				test_count--;
			}

			//
			// Be sure to close the stream from the exe output.
			//
			pclose( executable_output );
		}

		//
		// Get the current average
		//
		current_average = ( total_cycles / test_iterations );

		//
		// Replace the smallest average if warranted
		//
		if ( current_average > smallest_average ) {
			//
			// Replace the smallest and then find the new smallest
			//
			best_averages[smallest_index] = current_average;
			memset( best_patterns[smallest_index], 0, MAX_PATTERN_SIZE );
			strcpy( best_patterns[smallest_index], current_pattern );

			//
			// Find new the index of the smallest average
			//
			smallest_index = 0;
			smallest_average = best_averages[smallest_index];
			for( i = 1; i < MAX_BEST_PATTERNS; i++ ) {
				if( best_averages[i] < smallest_average ) {
					smallest_index = i;
					smallest_average = best_averages[smallest_index];
				}
			}
		}
	}

	for( i = 0; i < MAX_BEST_PATTERNS; i++ ) {
		printf( "Pattern [%s] took %d cycles\n", best_patterns[i], best_averages[i] );
	}

    return 0;
}
