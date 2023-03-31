// Implementation of the Set ADT using a balanced BST
// COMP2521 22T2 Assignment 1

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Set.h"
#include "SetStructs.h"

////////////////////////////////////////////////////////////////////////
// Basic Operations

void free_tree(struct node *root);
struct node *createnode(int item);
struct node *tree_insert(struct node *root, int item);
int tree_size(struct node *root);
bool find_tree_node(struct node *root, int item);
void tree_print(struct node *root);
void tree_union(Set s1, struct node *s2);
void node_qual_or_not(Set new, Set s1, struct node *s2, bool flag);
int Ceil(struct node* root, int item);
int Floor(struct node *root, int item);
int TreeHeight(struct node *t);
void rotateleft(struct node *root);
void rotateright(struct node *root);
struct node *find_smallest(struct node *root);
void check_do_rotate(struct node *root, int item);

/**
 * Creates a new empty set
 */
Set SetNew(void) {
    Set new = malloc(sizeof(Set));
    new->tree = NULL;
    new->smallest = NULL;

    return new;
}


// postorder traversal to free each node
// after free should give NULL
// avoid malicious person gets the root's information
void free_tree(struct node *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
    root = NULL;
}



/**
 * Frees all memory associated with the given set
 */
void SetFree(Set s) {
    if (s != NULL) {
        if (s->tree != NULL) {
            free_tree(s->tree);
            s->tree = NULL;  // avoid malicious person
        }
        s->smallest = NULL;
        free(s);
        s = NULL;            
    }
}

// give item to node's item, and initalize the node
struct node *createnode(int item) {
    struct node *tmp = malloc(sizeof(struct node));
    if (tmp == NULL) {
        printf("malloc fails\n");
        exit(1);
    }
    tmp->father = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->item = item;
    tmp->next = NULL;
    return tmp;
}





// insert node
// 1. use recursion to insert node
// 2. consider rotation when it's not avl tree
// 3. establish connection of node to node->next
// 4. return the root of the tree
struct node *tree_insert(struct node *root, int item) {
    if (root == NULL) {
        return createnode(item);
    } else if (item < root->item) {
        int if_null = 0;
        if (root->left == NULL) {
            if_null = 1;
        }
        root->left = tree_insert(root->left, item);
        if (if_null == 1) {
            if (root->father != NULL && root == root->father->right) {
                root->father->next = root;
            }
            root->left->next = root;
        }
        root->left->father = root;
    } else if (item > root->item) {
        int if_null = 0;
        if (root->right == NULL) {
            if_null = 1;
        }
        root->right = tree_insert(root->right, item);
        if (if_null == 1) {
            if (root->father != NULL && root == root->father->left) {
                root->right->next = root->father;
            }
            root->next = root->right;
        }
        root->right->father = root;
    }
    check_do_rotate(root, item);
    return root;
}

// use height of the subtree to check if should rotate 
void check_do_rotate(struct node *root, int item) {
    if ((TreeHeight(root->left) - TreeHeight(root->right)) > 1) {
        if (item > root->item) {
            rotateleft(root->left);
        }
        rotateright(root);
    } else if ((TreeHeight(root->left) - TreeHeight(root->right)) < -1) {
        if (item < root->item) {
            rotateright(root->right);
        }
        rotateleft(root);
    }
}

// rotate right
// note : change the father node
void rotateright(struct node *root) {
    struct node *new = root->left;
    if (root == NULL || new == NULL) {
        return;
    }
    root->left = new->right;                
    if (new->right != NULL) {
        new->right->father = root;
    }

    new->father = root->father;
    root->father = new;

    new->right = root;
}

// rotate left
// note : change the father node
void rotateleft(struct node *root) {
    struct node *new = root->right;
    if (root == NULL || new == NULL) {
        return;
    }
    root->right = new->left;
    if (new->left != NULL) {
        new->left->father = root;
    }

    new->father = root->father;
    root->father = new;

    new->left = root;
}




// find tree's height, using recursion
int TreeHeight(struct node *t) {
    if (t == NULL) {
        return 0;
    }
    int l = TreeHeight(t->left);
    int r = TreeHeight(t->right);
    return 1 + (l > r ? l : r); 
}

// find smallest node of tree.
// Time complexity O(logn) [the height of the tree]
struct node *find_smallest(struct node *root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->left != NULL) {
        root = find_smallest(root->left);
    }
    return root;
    
}

/**
 * Inserts an item into the set
 */
void SetInsert(Set s, int item) {
    s->tree = tree_insert(s->tree, item);
    s->smallest = find_smallest(s->tree);
}

//count all the nodes in the tree
int tree_size(struct node *root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + tree_size(root->left) + tree_size(root->right);
    }
}

/**
 * Returns the number of elements in the set
 */
int SetSize(Set s) {
    if (s == NULL || s->tree == NULL) {
        return 0;
    } else {
        return tree_size(s->tree);
    }
    
}


// Checks whether a value is in the given BSTree
bool find_tree_node(struct node *root, int item) {
    if (root == NULL) {
        return false;
    } else if (item < root->item) {
        return find_tree_node(root->left, item);
    } else if (item > root->item) {
        return find_tree_node(root->right, item);
    } else {
        return true;
    }
}
/**
 * Returns true if the set contains the given item, and false otherwise
 */
bool SetContains(Set s, int item) {
    return find_tree_node(s->tree, item);
}

// inorder traversal to print tree
void tree_print(struct node *root) {
    if (root == NULL) {
        return;
    }
    tree_print(root->left);
    printf("%d ", root->item);
    tree_print(root->right);
}


/**
 * Prints the given set in the format
 * {elem1, elem2, elem3}
 */
void SetShow(Set s) {
    tree_print(s->tree);
}

////////////////////////////////////////////////////////////////////////
// Further Operations

void tree_union(Set s1, struct node *s2) {
    if (s2 == NULL) {
        return;
    }
    SetInsert(s1, s2->item);
    tree_union(s1, s2->left);
    tree_union(s1, s2->right);
}

/**
 * Returns a new set representing the union of the two sets
 */
Set SetUnion(Set s1, Set s2) {
    if ((s1 == NULL || s1->tree == NULL) 
    && (s2 == NULL || s2->tree == NULL)) {
        return NULL;
    } else if (s1->tree == NULL) {
        return s2;
    } else if (s2->tree == NULL) {
        return s1;
    } else {
        Set new = SetNew();
        tree_union(new, s1->tree);
        tree_union(new, s2->tree);
        return new;
    }
    
}



/**
 * Returns a new set representing the intersection of the two sets
 */
Set SetIntersection(Set s1, Set s2) {
    if (s1 == NULL || s2 == NULL ||
    s1->tree == NULL || s2->tree == NULL) {
        return NULL;
    } else {
        Set new = SetNew();
        node_qual_or_not(new, s1, s2->tree, true);
        return new;
    }
}



/**
 * Returns a new set representing the set difference s1 - s2
 */
Set SetDifference(Set s1, Set s2) {
    if (s2 == NULL) {
        return s1;
    } else if (s1 == NULL) {
        return NULL;
    } else {
        Set new = SetNew();
        node_qual_or_not(new, s2, s1->tree, false);
        return new;
    }
}

// use preorder to check and insert
void node_qual_or_not(Set new, Set s1, struct node *s2, bool flag) {
    if (s2 == NULL) {
        return;
    }
    if (SetContains(s1, s2->item) == flag) {
        SetInsert(new, s2->item);
    }
    node_qual_or_not(new, s1, s2->left, flag);
    node_qual_or_not(new, s1, s2->right, flag);
}



/**
 * Returns true if the two sets are equal, and false otherwise
 */
bool SetEquals(Set s1, Set s2) {
    Set intersec_set = SetIntersection(s1, s2);
    Set union_set = SetUnion(s1, s2);
    if (SetSize(intersec_set) == SetSize(union_set)) {
        return true;
    } else {
        return false;
    }
    
}

/**
 * Returns true if set s1 is a subset of set s2, and false otherwise
 */
bool SetSubset(Set s1, Set s2) {
    Set intersec_set = SetIntersection(s1, s2);
    if (SetSize(intersec_set) == SetSize(s1)) {
        SetFree(intersec_set);
        return true;
    } else {
        SetFree(intersec_set);
        return false;
    }
    
}

// Base case
// If root's item is larger, floor must be in left subtree
// Else, either right subtree or root has the floor value
// exception for root->item 
// because it is being returned in base case
int Floor(struct node *root, int item) {
    
    
    if (root == NULL) {
        return UNDEFINED;
    }
    if (root->item > item) {
        return Floor(root->left, item);
    }
    
    else{
        int floor = Floor(root->right, item);
        
        if (floor <= item && floor != UNDEFINED) {
            return floor;
        } else {
            return root->item;
        }
    }
} 



/**
 * Finds the floor of a given item in a set
 */
int SetFloor(Set s, int item) {
    if (s->tree == NULL) {
        return UNDEFINED;
    } else {
        return Floor(s->tree, item);
    }
}


// same as Floor
int Ceil(struct node* root, int item) { 
    
    if (root == NULL) {
        return UNDEFINED;
    }
    if (root->item == item) {
        return root->item;
    }
    if (root->item < item) {
        return Ceil(root->right, item); 
    }
    else {
        
        int ceil = Ceil(root->left, item);
        if (ceil >= item && ceil != UNDEFINED) {
            return ceil;
        } else {
            return root->item;
        }
    }
    
} 

/** 
 * Returns the ceiling of a given item in a set
 */
int SetCeiling(Set s, int item) {
    if (s->tree == NULL) {
        return UNDEFINED;
    } else {
        return Ceil(s->tree, item);
    }
    
}

////////////////////////////////////////////////////////////////////////
// Cursor Operations

/**
 * Creates a new cursor positioned at the smallest element of the set
 */
SetCursor SetCursorNew(Set s) {
    struct cursor *new = malloc(sizeof(struct cursor));
    new->tree = s->smallest;

    
    
    return new;
}

/**
 * Frees all memory associated with the given cursor
 */
void SetCursorFree(SetCursor cur) {
    free(cur);
    cur = NULL;             // avoid malicious person
}

/**
 * Returns the element at the cursor's current position, and then moves
 * the cursor to the next greatest element. If there is no next greatest
 * element, then all subsequent calls to SetCursorNext on this cursor
 * should return UNDEFINED.
 */

int SetCursorNext(SetCursor cur) {
    int data = UNDEFINED;
    if (cur->tree != NULL) {
        data = cur->tree->item;
        cur->tree = cur->tree->next;
    }
    return data;
    
}


////////////////////////////////////////////////////////////////////////

// prev version

/* int SetCursorNext(SetCursor cur) {
    int data = UNDEFINED;
    //printf("item:%d\n", cur->tree->item);
    //printf("bool:%d\n", cur->tree->is_visited);
    //if (cur->tree->item == 4) {
    //  printf("item:%d\n", cur->tree->left->item);
    //  printf("bool:%d\n", cur->tree->left->is_visited);
    //}
    if (cur->tree == NULL) {
        return data;
    }
    if (cur->tree == cur->largest) {
        cur->tree->is_visited = true;
        data = cur->tree->item;
        //printf("--1--");
        cur->tree = cur->tree->right;
    } else if (cur->tree->left != NULL) {
        data = cur->tree->item;
        
        if (cur->tree->left != NULL 
        && cur->tree->left->is_visited == false) {    // move to left
            //printf("?\n");
            cur->tmp = cur->tree;
            while (cur->tree->left != NULL) {
                cur->tree = cur->tree->left;
                //cur->tree->is_visited = true;
            }
            cur->tree->is_visited = true;
            data = cur->tree->item;
        } else if (cur->tree->right != NULL) {
            cur->tree = cur->tree->right;
            cur->tmp = cur->tree;
        } else {
            cur->tree = cur->tree->father;
            cur->tmp = cur->tree;
        }
        //printf("--2--");
    } else if (cur->tree->right == NULL && cur->tree->left == NULL
     && cur->tree->father->left == cur->tree) { // left leaf node
        if (cur->tree->is_visited == true) {
            cur->tree = cur->tmp->right;
        } else {
            cur->tree->is_visited = true;
            data = cur->tree->item;
            cur->tree = cur->tree->father;
            cur->tmp = cur->tree;
        }
        
        //printf("--3--");
    } else if (cur->tree->right == NULL && cur->tree->left == NULL 
    && cur->tree->father->right == cur->tree) { // right leaf node 
        cur->tree->is_visited = true;
        data = cur->tree->item;
        if (cur->tmp->father != NULL) {  //won't occurs that case
            cur->tree = cur->tmp->father;
        }
        //printf("--4--");
    }
    //printf("\n");
    return data;
} */