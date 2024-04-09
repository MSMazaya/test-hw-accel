### Unit test Qupdate
```c
  setLSUMode(LSU_MODE_LEARNING_RATE);
  storeFloat(0.8, 0);
  qUpdate(0, 10.12);
```

```
  // PROBLEM: gabisa load di value yang sama setelah index pertama penyimpanan?
  // load(0);
  // load(1); // error disini
  // load(2);

  // PROBLEM: gabisa load setelah store terakhir sama nilainya dengan load pada address yang diinginkan?
  
  // PROBLEM: sama address gagal
  // float test = rand();

  // store(10.1, 0);
  // store(12.1, 1);
  // store(10.1, 2);
  // store(1230, 4);
  // store(12.1, 3);
  // store(12.1, 4);
  // store(12.1, 5);
  // store(12.1, 6);
  // store(12.1, 7);
  // store(12.1, 8);
  // store(12.1, 9);
  // store(12.1, 10);
  // store(12.1, 11);
  // store(12.1, 12);
  // store(12.1, 13);
  // store(12.1, 14);
  // store(12.1, 15);
  // store(12.1, 16);
  // store(12.1, 17);
  // store(12.1, 18);
  // store(12.1, 19);
  // store(12.1, 20);
  // store(12.1, 21);
  // store(12.1, 22);
  // store(12.1, 23);
  // store(12.1, 24);
  // store(12.1, 25);
  // store(12.1, 26);
  // store(12.1, 27);
  // store(12.1, 28);
  // store(12.1, 29);
  // store(12.1, 30);
  // store(12.1, 31);
  // still does not work, fix the ram!
  // you cache the value, but the value can be the same
  // you really want to make sure you use a read_enable and check if the
  // read_enable is changed instead of prev == new then say ok store(10.11,0);
  // float test = load(0);
  // store(4.123,1);
  // store(5.123, 1);
  // store(7.123, 2);
  // test = load(0);
  // initializeQTable();
  // storeQtoRam();
  // store(12.123, 12);
  // storeQtoRam();
  // float a = load(12);
  // float b = load(0);
  // float c = load(1);
  // store(100, 4);
  // store(231.21, 4);
  // store(1231.1, 4);
  // q_table[0][0][0] = load(32);
  // float f = load(1); // FAIL: always fail here
  // float g = load(2);
  // float t = load(0);
  // loadFromRam();
  // load(3);
```


temp
```
#include <stdlib.h>
#include <sys/_intsup.h>
#include <bsp_printf.h>
#include <bsp_mem_map.h>
#include <bsp_version.h>
#include <psp_api.h>
#include "ee_printf.h"
#include <uart.h>
// #include "accelerator_bsp.h"
// #include "timer_bsp.h"
// #include "utils.h"
// #include "maze.h"
// extern void uart_send_char(char c);

int main() {
  uart_send_char('a');
  // initMaze();
  // printMaze();
  // generateMaze();
  // printMaze();
  while (1);
}

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

```