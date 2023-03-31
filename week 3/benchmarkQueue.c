
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

int main(void) {
	Queue q = QueueNew();

	// TODO
	// Write a benchmark test to demonstrate the difference in
	// efficiency between ArrayQueue and CircularArrayQueue

	
	// enqueue 100000
	for (int i = 0; i < 200000; i++) {
		QueueEnqueue(q, i);
	}
	
	// dequeue 1 to 40000, enqueue 200001 to 240000
	for (int i = 200001, j = 0; i < 240000; i++, j++) {
		QueueEnqueue(q, i);
		QueueDequeue(q);
	}
	printf("abcdefghijklmnopqrstuvwxyz\n");

	QueueFree(q);
}

