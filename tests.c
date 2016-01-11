
#include <stdio.h>
#include <stdlib.h>
#include "io.h"

/*
 * Test helper
 */

int count = 0;

void fail(char *message) {
	printf("%s\n", message);
	exit(1);
}

/*
 * Tests
 */

void test_create_reader() {
	int error = create_reader();

	if (error != 0) {
		fail("Cannot create reader");
	}
}

void test_read_a_byte() {
	int byte = read_byte();

	if (byte != 'H') {
		fail("First byte is not H !");
	}
}

void test_read_two_bits() {
	int bit1 = read_bit();
	int bit2 = read_bit();

	if (bit1 != 0) {
		fail("Next bit not 0 !");
	}
	if (bit2 != 1) {
		fail("Next next bit not 1 !");
	}
}

void test_read_next_byte() {
	int byte = read_byte();

	if (byte != 149) {
		fail("Next byte is wrong !");
	}
}

void test_create_writer() {
	int error = create_writer();

	if (error == 1) {
		fail("Error while opening file for writing !");
	}
}

void test_write_byte() {
	int error = write_byte('4');

	if (error != 0) {
		fail("Error happens when writing byte");
	}
}

void test_write_bits_and_byte() {
	int error = write_bit(0);
	error = error | write_bit(0);
	error = error | write_byte(200);

	if (error != 0) {
		fail("Error happens when writing bits and byte");
	}
}

void test_flush_on_end() {
	write_bit(0);
	write_bit(0);
	write_bit(1);
	write_bit(0);
	write_bit(1);

	delete_writer();
}

// Just add the test function here for running it
void(*all_tests[])(void) = {
	&test_create_reader,
	&test_read_a_byte,
	&test_read_two_bits,
	&test_read_next_byte,
	&test_create_writer,
	&test_write_byte,
	&test_write_bits_and_byte,
	&test_flush_on_end
};

int main() {
	// Index
	int i;

	// Compute the numbers for tests
	int number = sizeof(all_tests)/sizeof(all_tests[0]);

	// Run each test
	for (i = 0 ; i < number ; ++i) {
		(all_tests[i])();
		++count;
	}

	printf("Tests passed : %d\n", count);

	return 0;
}
