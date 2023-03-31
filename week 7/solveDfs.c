// DFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

bool solve(Maze m) {
    // TODO: Complete this function
    //       Feel free to add helper functions
    int height = MazeHeight(m);
    int width = MazeWidth(m);

    bool **is_visit = createBoolMatrix(height, width);
    Cell **prev = createCellMatrix(height, width);

    Stack s = StackNew();
    Cell start = MazeGetStart(m);
    StackPush(s, start);


    bool if_find = false;
    while (!if_find && !StackIsEmpty(s)) {
        Cell curr = StackPop(s);
        if (is_visit[curr.row][curr.col] == true) {
            continue;
        }
        is_visit[curr.row][curr.col] = true;
        // exit and find the path
        if (MazeVisit(m, curr) == true) {
            while (curr.row != start.row || curr.col != start.col) {
                MazeMarkPath(m, curr);
                curr = prev[curr.row][curr.col];
            }
            
            MazeMarkPath(m, start);
            if_find = true;
            break;
        }
        // find the next step Cell will go
        Cell new[4] = {
            {.row = curr.row - 1, .col = curr.col},
            {.row = curr.row, .col = curr.col + 1},
            {.row = curr.row + 1, .col = curr.col},
            {.row = curr.row, .col = curr.col - 1},
        };
        // if find , enqueue
        for (int i = 0; i < 4; i++) {
            Cell tmp = new[i];
            if (tmp.row >= 0 && tmp.row < height && tmp.col >= 0 && tmp.col < width
            && MazeIsWall(m, tmp) == false && is_visit[tmp.row][tmp.col] == false) {
                StackPush(s, tmp);
                prev[tmp.row][tmp.col] = curr;
            }
        }
    }
    StackFree(s);
    freeBoolMatrix(is_visit);
    freeCellMatrix(prev);
    return if_find;
}

