// sortIntList.c - a program for testing IntListSortedCopy

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IntList.h"

int main(int argc, char *argv[]) {
	bool verbose = (argc == 2 && strcmp(argv[1], "-v") == 0);

	// read in the list
	IntList list = IntListRead(stdin);
	if (verbose) {
		printf("Original:\n");
		IntListShow(list);
	}

	// make a sorted copy of the list
	IntList sortedList = IntListSortedCopy(list);
	IntListFree(list);

	if (verbose) printf("Sorted:\n");
	IntListShow(sortedList);

	// make sure the list is consistent/sorted
	bool ok = IntListOK(sortedList);
	bool sorted = IntListIsSorted(sortedList);
	IntListFree(sortedList);

	if (!ok) {
		fprintf(stderr,
		        "\n"
		        "#####  ####   ####   #####  ####\n"
		        "#      #   #  #   #  #   #  #   #\n"
		        "####   ####   ####   #   #  ####\n"
		        "#      #  #   #  #   #   #  #  #\n"
		        "#####  #   #  #   #  #####  #   #\n"
		        "\n"
		        "error: IntListOK returned false, which means the list "
		        "was not updated correctly. Please see the IntListOK "
		        "function for details.\n");
		exit(EXIT_FAILURE);
	} else if (!sorted) {
		fprintf(stderr, "error: the list is not actually sorted\n");
		exit(EXIT_FAILURE);
	}
}

