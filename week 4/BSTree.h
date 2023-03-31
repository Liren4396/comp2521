// Interface to the binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H

#include <stdbool.h>

typedef struct BSTNode *BSTree;

////////////////////////////////////////////////////////////////////////

// Creates a new empty BSTree
BSTree BSTreeNew(void);

// Frees all the memory associated with the given BSTree
void BSTreeFree(BSTree t);

// Inserts a new value into the given BSTree and returns the root of the
// updated BSTree. Does not insert duplicate values.
BSTree BSTreeInsert(BSTree t, int v);

// Checks whether a value is in the given BSTree.
bool BSTreeFind(BSTree t, int v);

// Prints a BSTree to the given file.
// Assumes that the file is open for writing.
void BSTreePrint(BSTree t, FILE *out);

// Prints a BSTree to stdout.
void BSTreeShow(BSTree l);

////////////////////////////////////////////////////////////////////////

// Counts the number of nodes in the given BSTree
int BSTreeNumNodes(BSTree t);

// Counts the number of leaves in the given BSTree
int BSTreeNumLeaves(BSTree t);

// Deletes all of the leaves in the given BSTree and returns the root of
// the updated BSTree
BSTree BSTreeDeleteLeaves(BSTree t);

////////////////////////////////////////////////////////////////////////

// Prints the in-order traversal of the given BSTree
void BSTreeInOrder(BSTree t);

// Prints the pre-order traversal of the given BSTree
void BSTreePreOrder(BSTree t);

// Prints the post-order traversal of the given BSTree
void BSTreePostOrder(BSTree t);

// Prints the level-order traversal of the given BSTree
void BSTreeLevelOrder(BSTree t);

////////////////////////////////////////////////////////////////////////

#endif

