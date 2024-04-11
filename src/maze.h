#pragma once
#include "action.h"
#include "boolean.h"
#include <stdlib.h>
#include "ee_printf.h"

#define maze_dimension 4    

bool getIndexFromAction(int *row, int *col, int act);
void initMaze();
void createPathToGoal();
bool isWall(int row, int col);
bool isTargetOrOrigin(int row, int col);
void helperGenerateMaze(int row, int col);
void generateMaze();
void printMaze();
void copyMazeToCache();
void copyCacheToMaze();
void initializeQTable();
void leaveTrace(int row, int col);
int fastestStep();
bool isTraced(int row, int col);
int helperFastestStep(int row, int col,
                      int memo[maze_dimension][maze_dimension],
                      int maze_traced[maze_dimension][maze_dimension],
                      int steps_taken);