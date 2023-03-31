
#include "list.h"

int numDupesInOrderedList(List l) {
	// TODO
	int count = 0;
	for (Node new = l->head; new->next != NULL; new = new->next) {
		if (new->value == new->next->value) {
			count++;
		}
	}
	return count;
}

