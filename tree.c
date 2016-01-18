
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

void swap_in_tree(Tree* recto, Tree* verso) {
    Tree* recto_parent = recto->parent;
    Tree* verso_parent = verso->parent;

    // Swap children
    if (recto_parent->left == recto) {
        recto_parent->left = verso;
    } else {
        recto_parent->right = verso;
    }
    if (verso_parent->left == verso) {
        verso_parent->left = recto;
    } else {
        verso_parent->right = recto;
    }

    // Swap parent
    recto->parent = verso_parent;
    verso->parent = recto_parent;
}
