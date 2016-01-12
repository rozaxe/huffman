
#include <stdlib.h>
#include "tree.h"

/*
 * Private functions
 */

Tree* new_point() {
    Tree* point = (Tree*) malloc(sizeof(Tree));
    point->parent = NULL;
    point->weight = 0; // No weight
    point->index = -1; // Unorded by default
    return point;
}

/*
 * Public functions
 */

Tree* new_leaf(int character) {
    Tree* leaf = new_point();
    leaf->is_node = 0;
    leaf->character = character;
    return leaf;
}

Tree* new_node(Tree* left, Tree* right) {
    Tree* node = new_point();
    node->is_node = 1;
    node->left = left;
    node->right = right;
    return node;
}
