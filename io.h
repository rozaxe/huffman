
/*
 *  Reading functions
 */

// Set filename of input file to open
void set_input(char*);

// Call this fonction before reading
int create_reader();

// Call this function when done reading
int delete_reader();

// Return the next byte read from the file
int read_byte();

// Return the next bit read from the file
int read_bit();

/*
 * Writing functions
 */

// Set filename of output file to open
void set_output(char*);

// Call this function before writing
int create_writer();

// Call this function when done writing
int delete_writer();

// Append the byte to file
int write_byte(int);

// Append the bit to file
int write_bit(int);
