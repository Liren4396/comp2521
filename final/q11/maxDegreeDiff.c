
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"



int maxDegreeDiff(Graph g) {
    
    int num = g->nV;
    int arr[num];
    for (int i = 0; i < num; i++) {
        arr[i] = 0;
        
    }
    for (int i = 0; i < num; i++) {
        AdjList curr = g->edges[i];
        while (curr != NULL) {
            arr[i]++;
            if (g->edges[curr->v] == NULL) {
                arr[i]++;
            }
            arr[curr->v]--;
            curr = curr->next;
        }
    }
    int max = 0;
    for (int i = 0; i < num; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

