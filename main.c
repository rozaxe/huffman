
#include <stdio.h>
#include "huffman.h"

int main(int argc, char *argv[]) {

    if (argc > 1) {
        // Argument specified

        // For now, just compress it
        compress();

    } else {
        // Tell how to use program
        printf("You must specified at least one argument !\n");
    }

    return 0;
}
