#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Set.h"
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

void testSetInsert(void);
void testSetSize(void);
void testSetContains(void);
void testSetShow(void);

void testSetUnion(void);
void testSetIntersection(void);
void testSetDifference(void);
void testSetEquals(void);
void testSetSubset(void);
void testSetFloor(void);
void testSetCeiling(void);

void testSetCursor(void);
void test01(void);
void test02(void);
void test03(void);
void test04(void);

int main(int argc, char *argv[]) {
	testSetInsert();
/* 	testSetSize();
	testSetContains();
	testSetShow();

	testSetUnion();
	testSetIntersection();
	testSetDifference();
	testSetEquals();
	testSetSubset();
	testSetFloor();
	testSetCeiling();

	testSetCursor();
	
    test01();
	test02();
	test03();
	test04(); */
}
static int TreeHeight(struct node *t) {
    if (t == NULL) {
        return 0;
    }
    int l = TreeHeight(t->left);
    int r = TreeHeight(t->right);
    return 1 + (l > r ? l : r); 
}
void testSetInsert(void) {
	// NOTE: SetInsert can't be tested on its own unless we have direct
	//       access to the internal representation of the ADT, so you
	//       may want to #include "SetStructs.h" and then access
	//       s->tree

	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 4);
	
	
	assert(SetSize(s) == 3);
	
	printf("%d \n", TreeHeight(s->tree->left));
	printf("%d \n", TreeHeight(s->tree->right));
	SetFree(s);
}

void testSetSize(void) {
	Set s = SetNew();
	assert(SetSize(s) == 0);
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	assert(SetSize(s) == 4);
	SetInsert(s, 7);
	SetInsert(s, 2);
	assert(SetSize(s) == 5);

	SetFree(s);
}

void testSetContains(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	assert(SetContains(s, 2));
	assert(SetContains(s, 4));
	assert(SetContains(s, 5));
	assert(SetContains(s, 8));
	assert(!SetContains(s, 3));

	SetFree(s);
}

void testSetShow(void) {
	// SetShow can't be tested with assert, since it prints to stdout.
	// Therefore, it must be manually checked.

	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	SetShow(s);
	printf("\n");

	SetFree(s);
}

void testSetUnion(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);

	Set c = SetUnion(a, b);
	assert(SetContains(c, 2));
	assert(SetContains(c, 3));
	assert(SetContains(c, 4));
	assert(SetContains(c, 5));
	assert(SetContains(c, 7));
	assert(SetContains(c, 8));
	assert(SetSize(c) == 6);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetIntersection(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);

	Set c = SetIntersection(a, b);
	assert(SetContains(c, 5));
	assert(SetContains(c, 8));
	assert(!SetContains(c, 2));
	assert(!SetContains(c, 3));
	assert(!SetContains(c, 4));
	assert(!SetContains(c, 7));
	assert(SetSize(c) == 2);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetDifference(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);

	Set c = SetDifference(a, b);
	assert(SetContains(c, 2));
	assert(SetContains(c, 4));
	assert(!SetContains(c, 3));
	assert(!SetContains(c, 5));
	assert(!SetContains(c, 7));
	assert(!SetContains(c, 8));
	assert(SetSize(c) == 2);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetEquals(void) {
	Set a = SetNew();
	SetInsert(a, 4);
	SetInsert(a, 2);
	SetInsert(a, 7);
	SetInsert(a, 1);

	Set b = SetNew();
	SetInsert(b, 2);
	SetInsert(b, 4);
	SetInsert(b, 1);
	SetInsert(b, 7);
	
	Set c = SetNew();
	SetInsert(c, 4);
	SetInsert(c, 2);
	SetInsert(c, 7);
	SetInsert(c, 3);

	assert(SetEquals(a, b));
	//assert(!SetEquals(a, c));

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetSubset(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 3);
	SetInsert(a, 6);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 9);
	SetInsert(b, 5);
	SetInsert(b, 6);

	Set c = SetNew();
	SetInsert(c, 4);
	SetInsert(c, 6);
	SetInsert(c, 3);
	SetInsert(c, 7);

	assert(SetSubset(a, b));
	assert(!SetSubset(a, c));

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetFloor(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	//printf("7:%d\n", SetFloor(s, 7));
	//printf("4:%d\n", SetFloor(s, 4));
	//printf("1:%d\n", SetFloor(s, 1));
	assert(SetFloor(s, 7) == 5);
	assert(SetFloor(s, 4) == 4);
	assert(SetFloor(s, 1) == UNDEFINED);

	SetFree(s);
}

void testSetCeiling(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	//printf("%d\n", SetCeiling(s, 2));
	//printf("%d\n", SetCeiling(s, 6));
	//printf("%d\n", SetCeiling(s, 9));
	assert(SetCeiling(s, 2) == 2);
	assert(SetCeiling(s, 6) == 8);
	assert(SetCeiling(s, 9) == UNDEFINED);

	SetFree(s);
}

void testSetCursor(void) {
	Set s = SetNew();
/* 	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4); */
	SetInsert(s, 1);
	SetInsert(s, 2);
	SetInsert(s, 3);
	SetInsert(s, 4);
	SetInsert(s, 5);
	SetCursor cur = SetCursorNew(s);


	printf("%d\n", SetCursorNext(cur));
	printf("%d\n", SetCursorNext(cur));
	printf("%d\n", SetCursorNext(cur));
	printf("%d\n", SetCursorNext(cur));
	printf("%d\n", SetCursorNext(cur));
	printf("%d\n", SetCursorNext(cur));
/* 	assert(SetCursorNext(cur) == 2);
	assert(SetCursorNext(cur) == 4);
	assert(SetCursorNext(cur) == 5);
	assert(SetCursorNext(cur) == 8);
	assert(SetCursorNext(cur) == UNDEFINED); */
	
	SetFree(s);
	SetCursorFree(cur);
	printf("passed given tests\n");
}

void test01(void) {
	Set s = SetNew();
	SetCursor cur1 = SetCursorNew(s);
    assert(SetCursorNext(cur1) == UNDEFINED);
	assert(SetCursorNext(cur1) == UNDEFINED);
	
	assert(SetFloor(s, 1) == UNDEFINED);
	assert(SetCeiling(s, 1) == UNDEFINED);
	
    SetInsert(s, 5);
    assert(SetCursorNext(cur1) == UNDEFINED);
    SetCursor cur2 = SetCursorNew(s);

    assert(SetCursorNext(cur2) == 5);
    assert(SetCursorNext(cur2) == UNDEFINED);
    assert(SetCursorNext(cur2) == UNDEFINED);
    
    SetInsert(s, 5);
    
    
	
	Set a = SetNew();
	Set b = SetNew();
	Set c = SetUnion(a, b);
	

	SetFree(s);
	SetFree(a);
	SetFree(b);
	SetFree(c);


	SetCursorFree(cur1);
	SetCursorFree(cur2);



    printf("passed test01\n");
}

void test02(void) {
	Set s = SetNew();

	for (int i = 0; i <= 2<<7; i++) {
        
        SetInsert(s, i);
        
    }
	
	
	SetCursor cur = SetCursorNew(s);
	
    
    for (int i = 0; i <= 2<<7; i++) {
        
        int j = SetCursorNext(cur);
        //printf("%d == %d\n", i,j);   
        assert(j == i);
        
            
        //assert(SetCursorNext(cur) == i);
        
    }
    

	assert(SetCursorNext(cur) == UNDEFINED);
	assert(SetCursorNext(cur) == UNDEFINED);
	
	SetFree(s);
	SetCursorFree(cur);
	printf("passed test02\n");
}

void test03(void) {
	Set s = SetNew();
    Set s1 = SetNew();
    Set s2 = SetNew();
    
	
	SetInsert(s, 1);
	
	//printf("%d\n", SetFloor(s, 0));
	assert(SetFloor(s, 0) == UNDEFINED);
    assert(SetFloor(s, 1) == 1);
	assert(SetFloor(s, 2) == 1);
	
	
	assert(SetCeiling(s, 0) == 1);
    assert(SetCeiling(s, 1) == 1);
    assert(SetCeiling(s, 2) == UNDEFINED);
	
	
	assert(SetSize(s) == 1);
	assert(SetSize(s1) == 0);
	
	assert(!SetEquals(s1, s));

	//printf("%d\n", SetSize(s));
	//printf("%d\n", SetSize(s));
	//printf("%d\n", SetSize(s1));
	Set u1 = SetUnion(s, s1);
	printf("%d\n", SetSize(u1));
	assert(SetSize(u1) == 1);
	assert(SetFloor(u1, 0) == UNDEFINED);
    assert(SetFloor(u1, 1) == 1);
	assert(SetFloor(u1, 2) == 1);
	
	assert(SetCeiling(u1, 0) == 1);
    assert(SetCeiling(u1, 1) == 1);
    assert(SetCeiling(u1, 2) == UNDEFINED);
	
	
	
	Set u2 = SetUnion(s2, s1);
	assert(SetSize(u2) == 0);
	
	
	assert(SetEquals(u1, s));
	assert(SetEquals(s1, u2));
	
	
	
	
	Set i1 = SetIntersection(s, s1);
	assert(SetSize(i1) == 0);
	assert(SetEquals(i1, s1));
	Set i2 = SetIntersection(s2, s1);
    assert(SetSize(i2) == 0);
	assert(SetEquals(i2, s1));
	assert(SetEquals(i1, i2));
	
	Set d1 = SetDifference(s, s1);
	assert(SetSubset(d1, s));
    assert(!SetSubset(d1, s1));
	assert(SetSubset(s1, d1));
	
	SetShow(d1);
    SetShow(s);
	assert(SetSize(d1) == 1);
	assert(SetEquals(d1, s));
	
	assert(SetSize(d1) == 1);
    printf("%d\n", SetSize(d1));
    SetShow(d1);
    SetShow(s);
    
    
    assert(SetEquals(d1, s));
	
	
	
	assert(!SetEquals(d1, s1));
	assert(SetEquals(u1, d1));
	
	assert(SetEquals(u1, s));
	
	SetCursor cur = SetCursorNew(s);
	SetCursor cur1 = SetCursorNew(s1);
	
    assert(SetCursorNext(cur) == 1);
    
	assert(SetCursorNext(cur) == UNDEFINED);
	assert(SetCursorNext(cur) == UNDEFINED);
	assert(SetCursorNext(cur1) == UNDEFINED);
	
	SetFree(s);
	SetFree(s1);
	SetFree(s2);
	SetFree(u1);
	SetFree(u2);
	SetFree(i1);
	SetFree(i2);
	SetFree(d1);

	SetCursorFree(cur);
	SetCursorFree(cur1);
	printf("passed test03\n");
}



void test04(void) {
	Set s = SetNew();
    
	for (int i = 0; i < 256; i++) {
        
        SetInsert(s, i);
        
    }
	
	Set s1 = SetNew();
        
	for (int i = 0; i < 128; i++) {
        
        SetInsert(s1, i);
        
    }
	
	Set u1 = SetUnion(s, s1);
	assert(SetSize(u1) == 256);
    
    Set u2 = SetUnion(u1, s);
    
	assert(SetSize(u2) == 256);

	
	

	
	Set d1 = SetDifference(s, s1);
	assert(SetSubset(d1, s));
	assert(!SetSubset(s, d1));
    assert(!SetSubset(d1, s1));
	assert(!SetSubset(s1, d1));
	
    assert(!SetEquals(d1, s));
	assert(!SetEquals(d1, s1));
	assert(!SetEquals(u1, d1));
	assert(SetEquals(u1, s));
	
	Set i1 = SetIntersection(s, s1);
	assert(SetSize(i1) == 128);
	assert(SetEquals(i1, s1));
	assert(!SetEquals(i1, s));


    SetShow(i1);
    SetCursor cur = SetCursorNew(i1);
    
    for (int i = 0; i < 128; i++) {
        
        int j = SetCursorNext(cur);
        printf("%d == %d\n", i,j);   
        assert(j == i);
        
    }

/*
	SetCursor cur = SetCursorNew(d1);
	SetShow(d1);
    
    for (int i = 2<<6; i < 2<<7; i++) {
        
        int j = SetCursorNext(cur);
        printf("%d == %d\n", i,j);   
        assert(j == i);
        
    }
    
    printf("\n");
*/


    assert(SetSize(d1) == (2<<7)-(2<<6));
	assert(SetCursorNext(cur) == UNDEFINED);
	assert(SetCursorNext(cur) == UNDEFINED);
	
	
	SetFree(s);
	SetFree(s1);
	SetFree(u1);
	SetFree(u2);
	SetFree(i1);
	SetFree(d1);
	SetCursorFree(cur);
	printf("passed test04\n");
}
