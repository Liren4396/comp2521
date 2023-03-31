
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List flas(List l) {
    if (l == NULL) {
        return NULL;
    }
    int max_len = 0;
    
    List max;
    while (l->next != NULL && l != NULL) {

        List new = l;
        int len = 0;
        List curr = new;
        while (l->next->next != NULL && l->value < l->next->value) {
            len++;
            
            l = l->next;
            curr->next = l;
            curr = curr->next;
        }
        if (len > max_len) {
            max_len = len;
            max = new;
        }
        
        l = l->next;
    }
    if (max_len == 0) {
        return NULL;
    } else {
        return max;
    }
    
}

