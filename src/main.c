#include <stdlib.h>
#include <sys/_intsup.h>
#include <bsp_printf.h>
#include <bsp_mem_map.h>
#include <bsp_version.h>
#include <psp_api.h>
#include "ee_printf.h"
#include <uart.h>
#include "accelerator_bsp.h"
#include "timer_bsp.h"
#include "utils.h"
#include "maze.h"
#include "reinforcement_learning.h"

int main() {
  initPlatform();
  initMaze();
  generateMaze();
  copyMazeToCache();
  // startTimer();
  initializeQTable();
  train();
  // endTimer();
  // updateQ(0, 0, 1);
  lookResult();
  printTimerResult("sw");
  // ee_printf("Fastest step %d\n\n", fastestStep());
  // printMaze();
  // fastestStep();
  printQTable();
  while (1);
}

// UNIT TEST Q MAX
// int main() {
//   storeQValue(10.2, 0);
//   storeQValue(6.2, 1);
//   storeQValue(3.2, 6);
//   storeQValue(12.0, 12);

//   getMax(0);
//   getMax(4);
//   getMax(8);
//   getMax(12);
// }

// UNIT TEST Q QUEUE
// int main() {
//   // initPlatform();
//   setConstant(CONSTANT_TYPE_LEARNING_RATE, 0.4);
//   setConstant(CONSTANT_TYPE_DISCOUNT_FACTOR, 0.28);
//   storeQValue(10.2, 0);
//   storeQValue(6.2, 1);
//   storeQValue(3.2, 6);
//   storeQValue(12.0, 12);

//   load(0);

//   setNextState(1);
//   qUpdate(0, 2.5);

//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;
//   FOUR_NOPS;

//   load(0);
// }

// UNIT TEST Q Update
// int main() {
//   initPlatform();
//   setConstant(CONSTANT_TYPE_LEARNING_RATE, 0.4);
//   setConstant(CONSTANT_TYPE_DISCOUNT_FACTOR, 0.28);
//   storeQValue(10.2, 0);
//   storeQValue(6.2, 1);
//   storeQValue(3.2, 6);
//   storeQValue(12.0, 12);

//   float res = load(0);
//   res = load(1);
//   res = load(6);
//   res = load(12);

//   setNextState(1);
//   res = qUpdate(0, 2.5);

//   setNextState(5);
//   res = qUpdate(1, -0.8);
 
//   setNextState(5);
//   res = qUpdate(1, -0.8);

//   res = load(0);
//   res = load(1);
//   res = load(6);
//   res = load(12);
// }

// int main() {
//   initPlatform();
//   // setConstant(LSU_MODE_LEARNING_RATE);

//   //   float past = (1 - learnRate) * q_table[row][col][act];
//   //   float future = learnRate * (getReward(row, col, act) +
//   //                               discount * getNextMaxQ(row, col, act));
//   //   q_table[row][col][act] = past + future;

//   storeQValue(10.2, 0);
//   setConstant(CONSTANT_TYPE_LEARNING_RATE, 0.5);
//   setConstant(CONSTANT_TYPE_DISCOUNT_FACTOR, 0.28);
//   storeQValue(10.2, 6);
//   setNextState(5);
//   qUpdate(0, 2.5);

//   // startTimer();
//   // float res = qUpdate(0, 1.12);
//   // endTimer();
//   // printTimerResult("hw");

//   // float lr = 0.5;
//   // float q = 10.2;
//   // float d = 0.28;
//   // float r = 1.12;
//   // startTimer();
//   // float result = (1-lr)*q + lr*(r+d*q);
//   // endTimer();
//   // printTimerResult("sw");

//   // uart_send_float(result, 10);ee_printf("\n\n");
//   // uart_send_float(res, 10);ee_printf("\n\n");
//   // storeUnsignedInt(10, 0);
//   // storeUnsignedInt(1, 1);
//   // storeUnsignedInt(1202, 2);
//   // storeUnsignedInt(100, 3);
//   // initializeQTable();
//   // initializeQTableMemo();
//   // selectiveOverwriteQtable();
//   // printTimerResult("non-hw");
//   // unsigned int max_stored = loadUnsignedInt(0);
//   // for (int i = 1; i < 4; i++) {
//   //   unsigned int temp = loadUnsignedInt(i);
//   //   if(temp > max_stored) {
//   //     max_stored = temp;
//   //   }
//   // }
//   // endTimer();

//   // printTimerResult("Max by software");
//   // ee_printf("max = %d\n", max_stored);

//   // startTimer();
//   // unsigned int max_stored_hw = getMax(); // can only be used once, why?
//   // max_stored_hw = getMax(); // can only be used once, why?
//   // endTimer();

//   // printTimerResult("Max by hardware");
//   // ee_printf("max = %d\n", max_stored_hw);

//   // ee_printf("\n\n\n");
//   while(1);
// }
