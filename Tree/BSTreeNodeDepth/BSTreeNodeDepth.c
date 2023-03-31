
#include <stdlib.h>

#include "BSTree.h"

int BSTreeNodeDepth(BSTree t, int key) {
	if (t == NULL) {
        return -1;
    } else if (key == t->value) {
		return 0;
	} else if (key < t->value) {
		int depth = BSTreeNodeDepth(t->left, key);
		return (depth == -1 ? -1 : depth + 1);
	} else {
		int depth = BSTreeNodeDepth(t->right, key);
		return (depth == -1 ? -1 : depth + 1);
	}
}

