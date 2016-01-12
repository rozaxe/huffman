
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "tree.h"
#include "io.h"

/*
 * Private member variables
 */

// Store unknow leaf
Tree* unknow;

// Store virtual EOF
Tree* my_eof;

// Store root to Huffman tree
Tree* root;

// Store all point to Huffman tree orded by Gallager
Tree* gallager[517] = {0}; // 517 is the max numbers of point in a Huffman tree

// Store Gallager array size
int gallager_size;

// Store all ASCII leaf
Tree* ascii[256] = {0};

// Store path to a point
int path[257] = {0};

// Store path array size
int path_size;

/*
 * Private functions
 */

/* Initialization & Destruction */

// Initialize variables
void init_variables() {
    /* Tree */
    unknow = new_leaf('?');
    my_eof = new_leaf('0');

    // Create root
    root = new_node(my_eof, unknow);

    // Update leaf's parent
    unknow->parent = root;
    my_eof->parent = root;

    // Set weight
    my_eof->weight = 1;
    root->weight = 1;

    /* Gallager */
    // Basic array
    gallager[0] = root;
    gallager[1] = my_eof;
    gallager[2] = unknow;
    // Basic size
    gallager_size = 3;

    /* ASCII Array */
    path_size = 0;

    // Everything is initialized
}

// Initialize everything
void init() {
    int error;

    // Open files
    error = create_reader();
    if (error != 0) {
        printf("Error occuired while creating reader !\n");
        exit(1);
    }

    error = create_writer();
    if (error != 0) {
        printf("Error occuired while creating writer !\n");
        exit(2);
    }

    // Basic Huffman tree
    init_variables();
}

// Close files
void destroy() {
    // Close files
    delete_reader();
    delete_writer();
}

/* Huffman runtime functions */

// Fill the path with direction (left 0 / right 1) to retrieve root
// point -> root
void path_from(Tree* point) {
    Tree* current = point;

    // Go back up for each point
    while (current != NULL) {
        Tree* parent = current->parent;

        // Break if root reached
        if (parent == NULL) {
            break;
        }

        // Add direction to retrieve child
        if (parent->left == current) {
            // Left child
            path[path_size] = 0;
        } else {
            // Right child
            path[path_size] = 1;
        }

        // Next step
        ++path_size;
        current = parent;
    }
}

// Write path in reverse to ouput
// root -> point
void write_path_inverse() {
    // Index
    int i;

    // Write each direction as a bit
    for (i = path_size - 1 ; i >= 0 ; --i) {
        if (path[i] == 0) {
            // Left direction
            write_bit(0);
        } else {
            // Right direction
            write_bit(1);
        }
    }
}

/*
 * Public functions
 */

void compress() {

    init();

    // A byte is in [0, 255[
    int byte;

    // Read byte
    byte = read_byte();

    // ... Ignore it for now

    // EOF reached
    path_from(my_eof);
    write_path_inverse();

    // Compression is done
    destroy();
}

void uncompress() {

}
