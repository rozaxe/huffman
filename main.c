
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "huffman.h"

// Show how to use program
static void helper() {
    printf("\
Dynamic Huffman Coding - v1.0.1\n\
\n\
Usage: huffman (-h | <output_file> (-c|-u) <input_file>)\n\
  -c, --compress    Compress specified file\n\
  -u, --uncompress  Uncompress specified file\n\
  -h, --help        Display this message\n\
");
}

// Set input and ouput file
void match_files(char *argv[]) {
    set_output(argv[1]);
    set_input(argv[3]);
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

                if (strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "--compress") == 0) {
                    // Compress
                    match_files(argv);
                    compress();

                } else if (strcmp(argv[2], "-u") == 0 || strcmp(argv[2], "--uncompress") == 0) {
                    // Uncompress
                    match_files(argv);
                    uncompress();

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
