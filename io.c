
#include <stdio.h>
#include "io.h"

static FILE* input;

static char* input_filename = "input.txt";

int create_reader() {
	input = fopen(input_filename, "r");

	if (input == NULL) {
		return 1; // Error while opening file
	}
	return 0; // File opens
}

int delete_reader() {
	return 0;
}

int read_byte() {
	return fgetc(input);
}

int read_bit() {
	return 0;
}

