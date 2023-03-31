# COMP2521 - Lab 04 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = gcc
CFLAGS = -Wall -Werror -g

.PHONY: all
all: runBSTree testBSTree

runBSTree: runBSTree.o BSTree.o Queue.o
	$(CC) $(CFLAGS) -o runBSTree runBSTree.o BSTree.o Queue.o

testBSTree: testBSTree.o BSTree.o Queue.o
	$(CC) $(CFLAGS) -o testBSTree testBSTree.o BSTree.o Queue.o

runBSTree.o: runBSTree.c BSTree.h
testBSTree.o: testBSTree.c BSTree.h

BSTree.o: BSTree.c BSTree.h Queue.h
Queue.o: Queue.c Queue.h

.PHONY: clean
clean:
	rm -f *.o runBSTree testBSTree

