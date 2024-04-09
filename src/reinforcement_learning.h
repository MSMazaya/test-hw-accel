#pragma once
#include "maze.h"
#include "action.h"
#include "accelerator_bsp.h"
#define n_episode 1000
#define use_accelerator true

void saveQTableHistory(int episode);
int getBestAction(int row, int col);
float getReward(int row, int col, int action);
float getNextMaxQ(int row, int col, int act);
void updateQ(int row, int col, int act);
void train();
void lookResult();