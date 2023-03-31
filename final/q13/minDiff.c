
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

typedef struct queue *Queue;
typedef struct node1 *Node;

struct node1 {
	BSTree item;
	Node next;
};

struct queue {
	Node head;
	Node tail;
	int  size;
};

static Node newNode(BSTree it);
/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}
	
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}
/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	Node curr = q->head;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, BSTree it) {
	Node n = newNode(it);
	if (q->size == 0) {
		q->head = n;
	} else {
		q->tail->next = n;
	}
	q->tail = n;
	q->size++;
}

static Node newNode(BSTree it) {
	Node n = malloc(sizeof(*n));
	if (n == NULL) {
		fprintf(stderr, "couldn't allocate Node\n");
		exit(EXIT_FAILURE);
	}
	
	n->item = it;
	n->next = NULL;
	return n;
}
/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
BSTree QueueDequeue(Queue q) {
	assert(q->size > 0);
	
	Node newHead = q->head->next;
	BSTree it = q->head->item;
	free(q->head);
	q->head = newHead;
	if (newHead == NULL) {
		q->tail = NULL;
	}
	q->size--;
	return it;
}
/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}


int TreeHeight(BSTree t) {
    if (t == NULL) {
        return -1;
    }
    int l = TreeHeight(t->left);
    int r = TreeHeight(t->right);
    return 1 + (l > r ? l : r); 
}


int minDiff(BSTree t, int l) {
    Queue new = QueueNew();
	QueueEnqueue(new, t);
    int min = 100000;
    int depth = 0;
	while (QueueSize(new) > 0) {
        int diff = 0;
		
        depth++;
        int width = QueueSize(new);
        for (int i = 0; i < width; i++) {
            BSTree curr = QueueDequeue(new);
            if (l == depth && curr->left != NULL && curr->right != NULL) {
                if (curr->left->key > curr->right->key) {
                    diff = curr->left->key - curr->right->key;
                } else {
                    diff = curr->right->key - curr->left->key;
                }
            }
            
            //printf("%d\n", depth);
            if (diff < min && diff > 0) {
                min = diff;
            }
            //printf("%d ", diff);
            //printf("%d ", curr->key);
            if (curr->left != NULL) {

                
                QueueEnqueue(new, curr->left);
            }
            if (curr->right != NULL) {

                QueueEnqueue(new, curr->right);
            }
        }

	}
	QueueFree(new);
    if (min == 100000) {
        return 0;
    }
    return min;
}

