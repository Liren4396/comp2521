
#include "list.h"

bool listIsOrdered(List l) {
	int flag = 1;
	if (l->head == NULL) {
		return true;
	}
	while (l->head->value == l->head->next->value && l->head != NULL) {
		l->head = l->head->next;
	}
	if (l->head->value < l->head->next->value) {
		flag = 1;
	}
	//printf("%d\n", flag);
	if (l->head->value > l->head->next->value) {
		flag = -1;
	}
	Node new = l->head;
	while (new->next != NULL) {
		if (new->value < new->next->value) {
			//printf("%d\n", flag);
			if (flag == -1) {
				return false;
			}
		}
		if (new->value > new->next->value) {
			
			if (flag == 1) {
				return false;
			}
		}
		new = new->next;
	}
	return true;
}

