
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

// Just add the test function here for running it
void(*all_tests[])(void) = {
	&test_create_reader,
	&test_read_a_byte,
	&test_read_two_bits,
	&test_read_next_byte
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
