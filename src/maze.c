#include "maze.h"

bool maze[maze_dimension][maze_dimension];
bool maze_cache[maze_dimension][maze_dimension];
bool traversed[maze_dimension][maze_dimension];
int memo_create_route[maze_dimension][maze_dimension];
int desired_row = maze_dimension - 1, desired_col = maze_dimension - 1;
int DFSMaze[maze_dimension][maze_dimension];
int DFSMazeSteps = __INT_MAX__;

bool validIndex(int row, int col) {
  bool rowValid = (row > -1) && (row < maze_dimension);
  bool colValid = (col > -1) && (col < maze_dimension);
  return rowValid && colValid;
}

void leaveTrace(int row, int col) { maze[row][col] = 2; }

bool isTraced(int row, int col) { return maze[row][col] == 2; }

void copyMazeToCache() {
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      maze_cache[i][j] = maze[i][j];
    }
  }
}

void copyCacheToMaze() {
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      maze[i][j] = maze_cache[i][j];
    }
  }
}

bool getIndexFromAction(int *row, int *col, int act) {
  bool indexValid = false;
  switch (act) {
  case action_up:
    if (validIndex((*row) - 1, *col)) {
      (*row)--;
      indexValid = true;
    }
    break;
  case action_down:
    if (validIndex((*row) + 1, *col)) {
      (*row)++;
      indexValid = true;
    }
    break;
  case action_left:
    if (validIndex(*row, (*col) - 1)) {
      (*col)--;
      indexValid = true;
    }
    break;
  case action_right:
    if (validIndex(*row, (*col) + 1)) {
      (*col)++;
      indexValid = true;
    }
    break;
  default:
    ee_printf("Invalid action!\n");
    break;
  }
  return indexValid;
}


void initMaze() {
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      maze[i][j] = 1;
    }
  }
  maze[0][0] = 0;
}

void createPathToGoal() {
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      memo_create_route[i][j] = 0;
    }
  }
  int row = 0, col = 0;
  int max_additional_steps = maze_dimension / 2;
  while (row != desired_row || col != desired_col) {
    memo_create_route[row][col] = 1;
    int action =
        rand() %
        action_up; // so the only possible action is action_up and action_down
    if (max_additional_steps) {
      action = rand() % action_length;
      if (action > action_down) {
        max_additional_steps--;
      }
    }
    int prev_col = col, prev_row = row;
    getIndexFromAction(&row, &col, action);
    int visited_neighbor_cell = 0;
    for (int i = 0; i < action_length; i++) {
      int temp_col = col, temp_row = row;
      getIndexFromAction(&temp_row, &temp_col, i);
      if (maze[temp_row][temp_col] == 0) {
        visited_neighbor_cell++;
      }
    }
    if (visited_neighbor_cell > 1) {
      col = prev_col;
      row = prev_row;
    } else {
      maze[row][col] = 0;
    }
  }
}

bool isWall(int row, int col) { return maze[row][col] == 1; }

bool isTargetOrOrigin(int row, int col) {
  return (row == 0 && col == 0) ||
         (row == (maze_dimension - 1) && col == (maze_dimension - 1));
}

void helperGenerateMaze(int row, int col) {
  if (traversed[row][col]) {
    return;
  }
  int visited_neighbor_cell = 0;
  for (int act = 0; act < action_length; act++) {
    int temp_row = row, temp_col = col;
    getIndexFromAction(&temp_row, &temp_col, act);
    visited_neighbor_cell += validIndex(temp_row, temp_col) &&
                             !isWall(temp_row, temp_col) &&
                             !memo_create_route[row][col];
  }

  // if surrouding visited cell is not only one, stop
  if (visited_neighbor_cell > 1 && !isTargetOrOrigin(row, col)) {
    if (memo_create_route[row][col]) {
      if (visited_neighbor_cell != 2) {
        return;
      }
    } else {
      return;
    }
  }

  // else, do the algorithm:
  // 1. mark as visited/path (0)
  // 2. get list of walls
  // 3. pick random wall to be called for generateMaze
  traversed[row][col] = 1;
  maze[row][col] = 0;

  int to_traverse_left = 0;
  bool to_traverse[action_length];
  for (int act = 0; act < action_length; act++) {
    to_traverse[act] = false;
  }

  for (int act = 0; act < action_length; act++) {
    int temp_row = row, temp_col = col;
    getIndexFromAction(&temp_row, &temp_col, act);
    if ((validIndex(temp_row, temp_col) && isWall(temp_row, temp_col)) ||
        memo_create_route[temp_row][temp_col]) {
      to_traverse[act] = true;
      to_traverse_left++;
    }
  }

  while (to_traverse_left) {
    int first_chosen_valid_action = rand() % to_traverse_left;
    // first_chosen_valid_action is the first action that leads to "valid" wall
    int chosen_action = -1;
    for (int act = 0; act < action_length; act++) {
      if (to_traverse[act]) {
        if (first_chosen_valid_action != 0) {
          first_chosen_valid_action--;
        } else {
          chosen_action = act;
          break;
        }
      }
    }
    int temp_row = row, temp_col = col;
    getIndexFromAction(&temp_row, &temp_col, chosen_action);
    helperGenerateMaze(temp_row, temp_col);
    to_traverse[chosen_action] = false;
    to_traverse_left--;
  }
}


void generateMaze() {
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      traversed[i][j] = 0;
    }
  }
  createPathToGoal();
  helperGenerateMaze(0, 0);
}

int helperFastestStep(int row, int col,
                      int memo[maze_dimension][maze_dimension],
                      int maze_traced[maze_dimension][maze_dimension],
                      int steps_taken) {
  int local_memo[maze_dimension][maze_dimension];
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      local_memo[i][j] = memo[i][j];
    }
  }
  local_memo[row][col] = 1;

  // edge cases
  if (row == desired_row && col == desired_col) {
    maze_traced[row][col] = 2;
    if (steps_taken < DFSMazeSteps) {
      for (int i = 0; i < maze_dimension; i++) {
        for (int j = 0; j < maze_dimension; j++) {
          DFSMaze[i][j] = maze_traced[i][j];
        }
      }
      DFSMazeSteps = steps_taken;
    }
    return steps_taken;
  }
  if (!validIndex(row, col) || isWall(row, col)) {
    return maze_dimension * maze_dimension;
  }

  int result = __INT_MAX__;
  for (int act = 0; act < action_length; act++) {
    int r = row, c = col;
    getIndexFromAction(&r, &c, act);
    if (local_memo[r][c]) {
      continue;
    }
    maze_traced[row][col] = 2;
    int step =
        helperFastestStep(r, c, local_memo, maze_traced, steps_taken + 1);
    maze_traced[row][col] = 0;
    if (result > step)
      result = step;
  }

  return result;
}

int fastestStep() {
  int memo[maze_dimension][maze_dimension];
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      memo[i][j] = 0;
    }
  }
  int maze_traced[maze_dimension][maze_dimension];
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      maze_traced[i][j] = maze_cache[i][j];
    }
  }
  return helperFastestStep(0, 0, memo, maze_traced, 0);
}



void printMaze() {
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      ee_printf("%d", maze[i][j]);
    }
    ee_printf("\n");
  }
}
