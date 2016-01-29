
/*
 *  Reading functions
 */

// Set filename of input file to open
void set_input(char*);

// Return input filename
char* get_input();

// Return size (in bytes) of input file
off_t get_input_size();

// Return the head progression (in bytes) in input file
off_t get_input_current();

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

// Return ouput filename
char* get_output();

// Return the head progression (in bytes) in output file
off_t get_output_current();

// Call this function before writing
int create_writer();

// Call this function when done writing
int delete_writer();

// Append the byte to file
int write_byte(int);

// Append the bit to file
int write_bit(int);
