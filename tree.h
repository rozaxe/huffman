
// Tree structure
typedef struct self {
    // For every point
    int is_node;
    struct self *parent;

    // Custom tree field
    int weight;
    int index;

    // Only for leaf
    int character;

    // Only for node
    struct self *left;
    struct self *right;

} Tree;

// Return a new struct as a leaf
Tree* new_leaf(int character);

// Return a new struct as a node
Tree* new_node(Tree*, Tree*);
