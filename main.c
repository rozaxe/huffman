
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "huffman.h"

// Variables for verbose mode
static int last = -1;
static int clock = 0;

// Show how to use program
static void helper() {
    printf("\
Dynamic Huffman Coding - v2.0.0\n\
\n\
Usage: huffman [-h] [<output_file> (-c|-u) <input_file>]\n\
  -c, --compress    Compress specified file\n\
  -u, --uncompress  Uncompress specified file\n\
  -h, --help        Display this message\n\
");
}

// Set input and ouput file
static void match_files(int pos, char *argv[]) {
    set_output(argv[pos - 1]);
    set_input(argv[pos + 1]);
}

static void update() {
    int percent = ((float)get_input_current() / (float)get_input_size()) * 100;
    // Show percent only on change
    if (last != percent) {
        last = percent;
        clock = (clock + 1) % 8;

        char timer = '|';

        if (clock == 1 || clock == 5) {
            timer = '/';
        } else if (clock == 2 || clock == 6) {
            timer = '-';
        } else if (clock == 7 || clock == 3) {
            timer = '\\';
        }

        printf("\r%c %3d%% ", timer, percent);
        fflush(stdout);
    }
}

static void show_diff(int mode) {
    int percent = ((float)get_output_current() / (float)get_input_size()) * 100;
    printf("\n");
    if (mode == 'c') {
        printf("Compression");
    } else if (mode == 'u') {
        printf("Decompression");
    }
    printf(" rate : 100%% -> %d%%\n", percent);
}

// Run Huffman method based on command line usage
int main(int argc, char *argv[]) {

    // At least 1 argument
    if (argc > 1) {

        // Check if options are known
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            helper();

        } else {

            if (argc > 3) {

                // Where to find compress/uncompress option
                int look_at = 2;

                // Verbose mode
                int verbose = 0;
                if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--verbose") == 0) {
                    set_update(&update);
                    verbose = 1;
                    ++look_at; // Shift operand by one
                }

                if (strcmp(argv[look_at], "-c") == 0 || strcmp(argv[look_at], "--compress") == 0) {
                    // Compress
                    match_files(look_at, argv);
                    compress();

                    // Show compression rate
                    if (verbose == 1) {
                        show_diff('c');
                    }

                } else if (strcmp(argv[look_at], "-u") == 0 || strcmp(argv[look_at], "--uncompress") == 0) {
                    // Uncompress
                    match_files(look_at, argv);
                    uncompress();

                    // Show decompression rate
                    if (verbose == 1) {
                        show_diff('u');
                    }

                } else {
                    helper();
                }

            } else {
                helper();
            }

        }

    } else {
        helper();
    }

    return 0;
}
