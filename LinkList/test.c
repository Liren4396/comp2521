#include <stdio.h>
#include <stdlib.h>


typedef struct LinkList {
    int data;
    struct LinkList *next;
}list;

list *fn(list *l) {
    //Input: pointer to linked list node

    if (l == NULL)
        return NULL;
    if (l->next == NULL)
        return l;
    list *l2 = fn(l->next);
    l->next->next = l;
    l->next = NULL;
    return l2;
}
int main() {
    list *A = (list*)malloc(sizeof(list));
    list *B = (list*)malloc(sizeof(list));
    list *C = (list*)malloc(sizeof(list));
    list *D = (list*)malloc(sizeof(list));
    list *E = (list*)malloc(sizeof(list));
    A->data = 3;
    A->next = B;
    B->data = 7;
    B->next = C;
    C->next = D;
    C->data = 5;
    D->data = 3;
    D->next = E;
    E->next = NULL;
    E->data = 2;
    list *f = fn(A);
    for (list *cur = f; cur != NULL; cur = cur->next) {
        printf("%d->", cur->data);
    }
    printf("\n");
}