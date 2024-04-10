#include "timer_bsp.h"

unsigned int performanceCounter = 0;
int cyc_beg, cyc_end, cyc_delta;
int instr_beg, instr_end, instr_delta;
int BrCom_beg, BrCom_end, BrCom_delta;
int BrMis_beg, BrMis_end, BrMis_delta;
int totalCall = 0;

void initPlatform() {
   /* Initialize Uart */
   config_uart();

   pspMachinePerfMonitorEnableAll();

   pspMachinePerfCounterSet(D_PSP_COUNTER0, D_CYCLES_CLOCKS_ACTIVE);
   pspMachinePerfCounterSet(D_PSP_COUNTER1, D_INSTR_COMMITTED_ALL);
   pspMachinePerfCounterSet(D_PSP_COUNTER2, D_BRANCHES_COMMITTED);
   pspMachinePerfCounterSet(D_PSP_COUNTER3, D_BRANCHES_MISPREDICTED);
}

void startTimer() {
   cyc_beg = pspMachinePerfCounterGet(D_PSP_COUNTER0);
   instr_beg = pspMachinePerfCounterGet(D_PSP_COUNTER1);
   BrCom_beg = pspMachinePerfCounterGet(D_PSP_COUNTER2);
   BrMis_beg = pspMachinePerfCounterGet(D_PSP_COUNTER3);
}

void endTimer() {
   cyc_end = pspMachinePerfCounterGet(D_PSP_COUNTER0);
   instr_end = pspMachinePerfCounterGet(D_PSP_COUNTER1);
   BrCom_end = pspMachinePerfCounterGet(D_PSP_COUNTER2);
   BrMis_end = pspMachinePerfCounterGet(D_PSP_COUNTER3);
   cyc_delta += cyc_end-cyc_beg;
   instr_delta += instr_end-instr_beg;
   BrCom_delta += BrCom_end-BrCom_beg;
   BrMis_delta += BrMis_end-BrMis_beg;
   totalCall++;
}

void printTimerResult(const char* title) {
   ee_printf("============= %s =========\n", title);
   ee_printf("Cycles = %d\n", cyc_delta/totalCall);
   ee_printf("Instructions = %d\n", instr_delta/totalCall);
   ee_printf("BrCom = %d\n", BrCom_delta/totalCall);
   ee_printf("BrMis = %d\n", BrMis_delta/totalCall);
   performanceCounter++;
}

