#include "reinforcement_learning.h"
#include "accelerator_bsp.h"
#include "ee_printf.h"
#include "maze.h"

float cumulative_rewards[n_episode];
extern int desired_row, desired_col;
int iterationUntilReach = n_episode;
float learnRate = 0.7;
float discount = 0.3;

#define get_offset(row, col, act) (row* maze_dimension + col) * action_length + act

float q_table[maze_dimension][maze_dimension][action_length];
float q_table_history[maze_dimension][maze_dimension][action_length][n_episode];
float q_table_cache[maze_dimension][maze_dimension][action_length];

void saveQTableHistory(int episode) {
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      for (int k = 0; k < action_length; k++) {
        q_table_history[i][j][k][episode] = q_table[i][j][k];
      }
    }
  }
}

int getBestAction(int row, int col) {
  int chosen_action = 0;
  float max_q = q_table[row][col][chosen_action];
  for (int i = 1; i < action_length; ++i) {
    if (q_table[row][col][i] > max_q) {
      chosen_action = i;
      max_q = q_table[row][col][i];
    }
  }
  return chosen_action;
}

float getReward(int row, int col, int action) {
  bool indexValid = getIndexFromAction(&row, &col, action);

  if (!indexValid || isWall(row, col)) {
    // printf("INVALID\n");
    return -1;
  }

  if (isTraced(row, col)) {
    return -0.2;
  }

  if (row == desired_row && col == desired_col)
    return 1;

  return -0.01;
}

float getNextMaxQ(int row, int col, int act) {
  getIndexFromAction(&row, &col, act);
  float result = q_table[row][col][0];
  for (int i = 1; i < action_length; i++) {
    float next_q = q_table[row][col][i];
    if (result < next_q) {
      result = next_q;
    }
  }
  return result;
}


void updateQ(int row, int col, int act) {
  #ifdef use_accelerator
  int temp_row = row, temp_col = col;
  getIndexFromAction(&temp_row, &temp_col, act);
  setNextState(get_offset(temp_row, temp_col, act));
  qUpdate(get_offset(row, col, act), getReward(row, col, act));
  #else
  float past = (1 - learnRate) * q_table[row][col][act];
  float future = learnRate * (getReward(row, col, act) +
                              discount * getNextMaxQ(row, col, act));
  q_table[row][col][act] = past + future;
  #endif
}

// NOTE: may be unnecessary
void initializeQTable() {
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      unsigned int offset = (i * maze_dimension + j);
      for (int k = 0; k < action_length; k++) {
        #ifdef use_accelerator
        storeQValue(0, offset);
        #else
        q_table[i][j][k] = 0;
        #endif
      }
    }
  }
}


void train() {
  #ifdef use_accelerator
  setConstant(CONSTANT_TYPE_DISCOUNT_FACTOR, discount);
  setConstant(CONSTANT_TYPE_LEARNING_RATE, learnRate);
  #endif
  int episode_count = n_episode;
  for (int episode = 0; episode < episode_count; ++episode) {
    cumulative_rewards[episode] = 0;
    int row = 0, col = 0;
    int maxStep = maze_dimension * maze_dimension;
    while ((row != desired_row || col != desired_col) && maxStep != 0) {
      leaveTrace(row, col);
      int chosen_action;
      float exploration_probability = 0.2;
      if (rand() / (RAND_MAX + 1.0) < exploration_probability) {
        chosen_action = rand() % action_length;
      } else {
        chosen_action = getBestAction(row, col);
      }
      bool win = (row == desired_row && col == desired_col);
      float reward = getReward(row, col, chosen_action);
      cumulative_rewards[episode] += reward;
      updateQ(row, col, chosen_action);
      int prev_row = row, prev_col = col;
      bool indexValid = getIndexFromAction(&row, &col, chosen_action);
      if (!indexValid || isWall(row, col)) {
        row = prev_row;
        col = prev_col;
      }
      maxStep--;
    }
    copyCacheToMaze();
    if (maxStep != 0 && iterationUntilReach == n_episode) {
      iterationUntilReach = episode;
    }
    saveQTableHistory(episode);
  }
  #ifdef use_accelerator
  for (int i = 0; i < maze_dimension; i++) {
    for (int j = 0; j < maze_dimension; j++) {
      unsigned int offset = (i * maze_dimension + j);
      for (int k = 0; k < action_length; k++) {
        q_table[i][j][k] = load(get_offset(i, j, k));
      }
    }
  }
  #endif
}

// #define lookResult_print_maze true

void lookResult() {
  int row = 0, col = 0;
  int steps = 0;
  #ifdef lookResult_print_maze
  leaveTrace(row, col);
  #endif
  while (row != desired_row || col != desired_col) {
    #ifdef lookResult_print_maze
    printMaze();
    #endif
    int act = getBestAction(row, col);
    #ifdef lookResult_print_maze
    ee_printf("ROW = %d, COL = %d\n", row, col);
    #endif
    getIndexFromAction(&row, &col, act);
    #ifdef lookResult_print_maze
    printAction(act);
    leaveTrace(row, col);
    #endif
    steps++;
  }
  #ifdef lookResult_print_maze
  printMaze();
  #endif
  ee_printf("Total by RL: %d steps\n", steps);
}
