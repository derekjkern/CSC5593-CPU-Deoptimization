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

#define LINE_SIZE  				300
#define MAX_EXECUTABLE_COUNT	50

typedef struct __TestConfig {
  //
  // This will hold the number of iterations to be run.
  //
  unsigned int iterations;

  //
  // This will hold executables (and their designations) to be run.
  //
  char *executables[MAX_EXECUTABLE_COUNT];
} *TestConfig;

void split_command_line( char *line, char *command_description, char *command ) {
	//
	// Splits a command from its description.  Assumes that they are separated by
	// the first '=' sign.  The description is supposed to appear before the '=' sign.
	//
	int i = 0, j = 0;
	int found_delimiter = 0;

	while( ( (int) line[i] ) != 0 && line[i] != '\n' ) {
		if ( found_delimiter ) {
			command[j] = line[i];
		} else {
			if ( line[i] == '=' ) {
				found_delimiter = 1;

				//
				// Terminate the command description string
				//
				command_description[j] = (char) 0;

				//
				// Reset j since it must now index into the command.
				//
				// j will be incremented to zero at the end of this block.
				//
				j = -1;
			} else {
				command_description[j] = line[i];
			}
		}

		//
		// Increment the counters.
		//
		i++; j++;
	}

	//
	// Terminate the command string
	//
	command[j] = (char) 0;
}

TestConfig read_test_configuration( char *config_filename ) {
  //
  // Read in the test configuration from the provided filename. This configuration
  // file contains the information needed to test.
  //
  TestConfig config = (TestConfig) malloc( sizeof( struct __TestConfig ) );
  FILE *config_file = fopen ( config_filename, "rt" );
  char line[LINE_SIZE];
  int executables_seen = 0;
  int executable_count = 0;

  do {
    //
    // Leave when we hit the end of the file.
    //
    if ( fgets( line, LINE_SIZE, config_file ) == NULL ) {
      break;
    }

    //
    // First, see if this line is one of the basic config options.
    //
    if ( executables_seen == 0 && strchr( line, '=' ) != NULL ) {
      if ( strstr( line, "ITERATIONS=" ) != NULL ) {
		sscanf( line, "ITERATIONS=%lu", &config->iterations );
	  }
    } else {
      if ( strstr( line, "__EXECUTABLES__" ) != NULL ) {
		//
		// Indicate that we've seen the executable marker. The executable
		// data needs to appear last.
		//
		executables_seen = 1;
	  } else if ( strchr( line, '=' ) != NULL ) {
		//
		// Allocate the space the executable data.
		//
		config->executables[executable_count] = (char*) malloc( 200 * sizeof( char ) );

		//
		// Read in the executable information.
		//
		memcpy( config->executables[executable_count++], line, strlen( line ) + 1 );
      }
    }
  } while( 1 );

  //
  // Make sure that the next exe is null
  //
  if ( executable_count < MAX_EXECUTABLE_COUNT ) {
  	config->executables[executable_count] = NULL;
  }

  //
  // Make sure that the file gets closed.
  //
  fclose( config_file );

  return config;
}

void print_usage() {
	//
	// Use this procedure to let users know the command line format.
	//
	printf( "Invalid arguments to version_tester\n" );
	printf( "  Format:  version_tester <testing configuration filename>\n" );
	printf( "  Arguments:\n" );
	printf( "    testing configuration filename - Mandatory - This file contains a configuration\n" );
	printf( "                                     that instructs the version tester on what to do.\n" );
}

int main( int argc, char **argv ) {
	long long total_cycles = 0;
	unsigned long current_cycles;
	FILE *executable_output;
	char output_buffer[500], executable_run_command[300], executable_title[100];
	int i = 0, iteration_count;
	float executable_average;

	//
	// If we don't have enough parameters, then let the user know
	//
	if ( argc < 2 ) {
		print_usage();

		exit( 1 );
	}

	//
	// Read in the test config.
	//
	TestConfig config = read_test_configuration( argv[1] );

	//
	// Now, run each executable the prescribed number of times.
	//
	while ( i < MAX_EXECUTABLE_COUNT && config->executables[i] != NULL ) {
		//
		// Pull apart the executable name from its title.
		//
		split_command_line( config->executables[i], executable_title, executable_run_command );

		//
		// Indicate the start
		//
		printf( "Running %s for %d iterations\n", executable_title, config->iterations );

		//
		// Clear the total cycles for this executable.
		//
		total_cycles = 0;

		for( iteration_count = 0; iteration_count < config->iterations; iteration_count++ ) {
			//
			// Run the executable and capture the output.
			//
			executable_output = popen( executable_run_command, "r" );

			//
			// Read the cycles for this run and add them to the total.
			//
			fgets( output_buffer, 500, executable_output );
			sscanf( output_buffer, "Cycles=%lu\n", &current_cycles );
			total_cycles += current_cycles;

			//
			// Be sure to close the stream from the exe output.
			//
			pclose( executable_output );
		}

		//
		// Indicate the end
		//
		printf( "Done running %s with an average of %d cycles\n\n",
				executable_title, ( total_cycles / config->iterations ) );
		fflush( stdout );

		//
		// Go to the next executable.
		//
		i++;
	}

    return 0;
}
