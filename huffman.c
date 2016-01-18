
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
Tree* ascii[256] = {NULL};

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
    root->index = 0;
    my_eof->index = 1;
    unknow->index = 2;
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

//// Path

// Fill the path with direction (left 0 / right 1) to retrieve root
// point -> root
void path_from(Tree* point) {
    Tree* current = point;
    path_size = 0;

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

// Read direction from input until reaching a leaf
Tree* goto_leaf() {
	Tree* current = root;

	// For each node, go down
	while (current->is_node == 1) {

		int dir = read_bit();

		if (dir == 0) {
			// Left
			current = current->left;
		} else {
			// Right
			current = current->right;
		}

	}

	// Return leaf
	return current;
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

//// Array
void swap_in_gallager(Tree* recto, Tree* verso) {
    // Tree index
    int i = recto->index;
    int j = verso->index;

    // Basic swap
    Tree* temp = gallager[i];  // temp = recto
    gallager[i] = gallager[j]; // recto = verso
    gallager[j] = temp;        // verso = temp

    // Update index
    recto->index = j;
    verso->index = i;
}

// Check if the leaf tagged with c is already present in tree
int already_added(int c) {
    if (ascii[c] == NULL) {
        return 0; // Not present
    } else {
        return 1; // Present
    }
}

// Return higher point in gallager with same weight
Tree* higher_point_with_same_weight(Tree* point) {
    int index = point->index;

    Tree* previous = gallager[index];

    // Come back while it's the same weight and not root
    while (index > 0 && previous->weight == point->weight) {
        index -= 1;
        if (index == 0 || gallager[index]->weight != point->weight) {
            return previous;
        }
        previous = gallager[index];
    }

    // Return point with same weight
    //printf("\np %d %d\n", point->weight, previous->weight);
    return previous;
}

//// Tree

// Create a parent on top of unknow with a new leaf
void add_char(int c) {
    // New leaf
    Tree* leaf = new_leaf(c);

    // New node, pointing unknow and new leaf
    Tree* node = new_node(leaf, unknow);

    // Update parents
    if (unknow->parent->left == unknow) {
        unknow->parent->left = node;
    } else {
        unknow->parent->right = node;
    }
    node->parent = unknow->parent;
    leaf->parent = node;
    unknow->parent = node;

    // Fatten points
    leaf->weight = 1;
    node->weight = 1;

    // Update gallager
    gallager[unknow->index] = node;
    node->index = unknow->index;
    gallager[unknow->index + 1] = leaf;
    leaf->index = unknow->index + 1;
    gallager[unknow->index + 2] = unknow;
    unknow->index += 2;
    gallager_size += 2;

    // Add to ASCII
    ascii[c] = leaf;
}

// Fatten a point
void increment(Tree* point) {

    // Look for higher point with same weight
    Tree* higher = higher_point_with_same_weight(point);

    // Swap point
    if (higher != root) {
        swap_in_tree(point, higher);
        swap_in_gallager(point, higher);
    }

    // Fatten point
    point->weight += 1;
}

// Fatten a leaf and all of its parents
void increment_from(Tree* leaf) {
    Tree* current = leaf;

    // Fatten each point
    while (current != NULL) {
        increment(current);

        // Parent turn
        current = current->parent;
    }

    // Root reached
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

    // Compress each byte
    while (byte != EOF) {

        if (already_added(byte) == 1) {

            // Write path to leaf
            Tree* leaf = ascii[byte];
            path_from(leaf);
            write_path_inverse();

            // Update tree
            increment_from(leaf);

        } else {
            // New character

            // Write path to '?'
            path_from(unknow);
            write_path_inverse();

            // Write char
            write_byte(byte);

            // Add char to tree
            add_char(byte);

            // Update tree
            // New parent's weight of unknow is already set
            // Increase from grand parent
            increment_from(unknow->parent->parent);
        }

        // Read next byte
        byte = read_byte();
    }

    // EOF reached
    path_from(my_eof);
    write_path_inverse();

    // Compression is done
    destroy();
}

void uncompress() {

	init();

	// Leaf pointer
	Tree* leaf;

	// Get first leaf
	leaf = goto_leaf();

	// Do something until virtual EOF reached
	while (leaf != my_eof) {

        if (leaf == unknow) {
            // New char

            int byte = read_byte();
            write_byte(byte);

            // Add char
            add_char(byte);

            // Update tree
            increment_from(unknow->parent->parent);
        } else {
            // Char already present
            write_byte(leaf->character);

            // Update tree
            increment_from(leaf);
        }

        // Next leaf
        leaf = goto_leaf();
	}

	// Virtual EOF reached
	destroy();

	// Uncompression done
}
