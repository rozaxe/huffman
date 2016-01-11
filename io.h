
/*
 *  Reading functions
 */

// Call this fonction before reading
int create_reader();

// Call this function when done reading
int delete_reader();

// Return the next byte read from the file
int read_byte();

// Return the next bit read from the file 
int read_bit();
