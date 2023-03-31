
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    if (t == NULL) {
        return -1;
    }
    int l = TreeHeight(t->left);
    int r = TreeHeight(t->right);
    return 1 + (l > r ? l : r); 
}

