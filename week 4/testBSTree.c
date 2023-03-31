// testBSTree.c

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int main(void) {
	setbuf(stdout, NULL);

	BSTree t = BSTreeNew();

	int value = 0;
	while (scanf("%d", &value) == 1) {
		t = BSTreeInsert(t, value);
	}

	// Display information about constructed tree
	printf("Tree:\n");
	BSTreeShow(t);
	printf("\n");
	
	printf("#nodes:  %d\n", BSTreeNumNodes(t));
	printf("#leaves: %d\n", BSTreeNumLeaves(t));
	printf("\n");

	printf("In-order:    "); BSTreeInOrder(t);    printf("\n");
	printf("Pre-order:   "); BSTreePreOrder(t);   printf("\n");
	printf("Post-order:  "); BSTreePostOrder(t);  printf("\n");
	printf("Level-order: "); BSTreeLevelOrder(t); printf("\n");
	printf("\n");

	printf("Deleting all the leaves in the tree...\n");
	t = BSTreeDeleteLeaves(t);
	printf("New tree:\n");
	BSTreeShow(t);
	printf("\n");

	BSTreeFree(t);
}

