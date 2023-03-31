// Recursive DFS maze solver with backtracking

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
bool dfs(Maze m, Cell curr, int height, int width, Cell prev[curr.row][curr.col], bool is_visit[height][width]);
bool solve(Maze m) {

    int height = MazeHeight(m);
    int width = MazeWidth(m);

    bool **is_visit = createBoolMatrix(height, width);
    Cell **prev = createCellMatrix(height, width);

    //Stack s = StackNew();
    Cell start = MazeGetStart(m);
    //StackPush(s, start);


    bool if_find = dfs(m, start, height, width, prev[start.row][start.col], is_visit[start.row][start.col]);
    //Cell curr = StackPop(s);

    // exit and find the path
    // if (MazeVisit(m, curr) == true) {

    //     while (curr.row != start.row || curr.col != start.col) {
    //         MazeMarkPath(m, curr);
    //         curr = prev[curr.row][curr.col];
    //     }
        
    //     MazeMarkPath(m, start);
    //     if_find = true;
    //     break;
    // }
    
    //StackFree(s);
    freeBoolMatrix(is_visit);
    freeCellMatrix(prev);
    return if_find;
}

bool dfs(Maze m, Cell curr, int height, int width, Cell prev[curr.row][curr.col], bool is_visit[height][width]) {
    if (MazeVisit(m, curr) == true) {
        MazeMarkPath(m, curr);
        return true;
    }
    //if (is_visit[curr.row][curr.col] == true) {
    //    continue;
    //}
    is_visit[curr.row][curr.col] = true;
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
            return dfs(m, tmp, height, width, prev[tmp.row][tmp.col], is_visit[tmp.row][tmp.col]);
            prev[tmp.row][tmp.col] = curr;
        }
    }
}