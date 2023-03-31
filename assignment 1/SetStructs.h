// COMP2521 22T2 Assignment 1

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct node {
	int item;           // DO NOT CHANGE/REMOVE THIS FIELD
	struct node *left;  // DO NOT CHANGE/REMOVE THIS FIELD
	struct node *right; // DO NOT CHANGE/REMOVE THIS FIELD
	// You may add more fields here if needed
	struct node *father;   // return father node
	//bool is_visited;
	struct node *next; // return next node
	//struct node *prev; // return prev node
};

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct set {
	struct node *tree;  // DO NOT CHANGE/REMOVE THIS FIELD
	// You may add more fields here if needed
	struct node *smallest; // this node is the cursor's root node 
};


// You may define more structs here if needed 

////////////////////////////////////////////////////////////////////////
// Cursors

struct cursor {
	// You may add more fields here if needed
	struct node *tree;
};

////////////////////////////////////////////////////////////////////////

