
#include <stdio.h>
#include "io.h"

// Variables for handling input file
static FILE* input;
static int input_buffer;
static int input_buffer_size;
static char* input_filename = "input.file";

// Variables for handling output file
static FILE* output;
static int output_buffer;
static int output_buffer_size;
static char* output_filename = "output.file";

void set_input(char* name) {
	input_filename = name;
}

char* get_input() {
	return input_filename;
}

int create_reader() {
	// Open file
	input = fopen(input_filename, "r");
	input_buffer = 0;
	input_buffer_size = 0;

	if (input == NULL) {
		return 1; // Error while opening file
	}
	return 0; // File is opened
}

int delete_reader() {
	// Close file
	int error = fclose(input);
	if (error == EOF) {
		return 1; // Error
	}
	return 0; // Success
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
	input_buffer = input_buffer & ((1 << input_buffer_size) - 1);

	return bit;
}

void set_output(char* name) {
	output_filename = name;
}

char* get_output() {
	return output_filename;
}

int create_writer() {
	// Open file
	output = fopen(output_filename, "w");
	output_buffer = 0;
	output_buffer_size = 0;

	if (output == NULL) {
		return 1; // Error while opening file
	}
	return 0; // File is opened
}

int delete_writer() {
	// Flush remaining bits in buffer
	if (output_buffer_size > 0) {
		write_byte(0);
	}

	// Close file
	int error = fclose(output);
	if (error == EOF) {
		return 1; // Error
	}
	return 0; // Success
}

int write_byte(int byte) {
	int character;

	// Add byte to buffer
	output_buffer = (output_buffer << 8) | byte;

	// Get first byte from buffer
	character = output_buffer >> output_buffer_size;

	// Keep unused bits
	output_buffer = output_buffer & ((1 << output_buffer_size) - 1);

	// Append byte to file
	int code = fputc(character, output);

	if (code == EOF) {
		return 1; // Error while writing
	}
	return 0; // Success
}

int write_bit(int bit) {
	// Add bit to buffer
	++output_buffer_size;
	output_buffer = (output_buffer << 1) | bit;

	// Flush buffer if full
	if (output_buffer_size == 8) {
		int code = fputc(output_buffer, output);

		if (code == EOF) {
			return 1; // Error while writing
		}

		// Reset buffer
		output_buffer = 0;
		output_buffer_size = 0;
	}
	return 0; // Success
}
