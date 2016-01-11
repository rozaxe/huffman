
#include <stdio.h>
#include "io.h"

static FILE* input;
static int input_buffer;
static int input_buffer_size;

static char* input_filename = "input.txt";

int create_reader() {
	input = fopen(input_filename, "r");
	input_buffer = 0;
	input_buffer_size = 0;

	if (input == NULL) {
		return 1; // Error while opening file
	}
	return 0; // File opens
}

int delete_reader() {
	return 0;
}

int read_byte() {
	int byte = 0;

	// Add byte to queue
	byte = fgetc(input);
	input_buffer = input_buffer << 8;
	input_buffer = input_buffer | byte;

	// Consume a byte
	byte = input_buffer >> input_buffer_size;

	// Keep only last not used bit
	input_buffer = input_buffer & ((1 << input_buffer_size) - 1);

	// Return byte
	return byte;
}

int read_bit() {
	// Store bit
	int bit;

	if (input_buffer_size == 0) {
		// Add next byte to buffer
		input_buffer = fgetc(input);

		if (input_buffer == EOF) {
			return EOF; // EOF reached
		}

		// 8 bits into buffer
		input_buffer_size = 8;
	}

	// Consume a bit from buffer
	--input_buffer_size;
	bit = (input_buffer & (1 << input_buffer_size)) >> input_buffer_size;
	input_buffer = input_buffer & ((1 <<input_buffer_size) - 1);

	return bit;
}
