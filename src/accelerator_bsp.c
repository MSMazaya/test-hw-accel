#include "accelerator_bsp.h"

void setConstant(ConstantType mode, float value) {
  asm volatile("lw t3, %0;" : "=m"(mode));
  asm volatile("lw t4, %0;" : "=m"(value));
  
  FOUR_NOPS;
  asm volatile(".word 0x1fce8f53;");
  FOUR_NOPS;
}

void setNextState(unsigned int next_state) {
  unsigned int next_state_type = CONSTANT_TYPE_NEXT_STATE;
  asm volatile("lw t3, %0;" : "=m"(next_state_type));
  asm volatile("lw t4, %0;" : "=m"(next_state));
  
  FOUR_NOPS;
  asm volatile(".word 0x1fce8f53;");
  FOUR_NOPS;
}

float qUpdate(unsigned int q_table_address, float reward) {
  float result;
  
  asm volatile("lw t3, %0;" : "=m"(q_table_address));
  asm volatile("lw t4, %0;" : "=m"(reward));

  FOUR_NOPS;
  asm volatile(".word 0x1dce8f53;");
  FOUR_NOPS;

  __asm__ volatile("sw t5, %0;" : "=m"(result));

  return result;
}

float storeQValue(float value, unsigned int address) {
  float result;

  asm volatile("lw t3, %0;" : "=m"(address));
  asm volatile("lw t4, %0;" : "=m"(value));

  FOUR_NOPS;
  asm volatile(".word 0x01ce8f53;");
  FOUR_NOPS;

  __asm__ volatile("sw t5, %0;" : "=m"(result));

  return result;
}

float storeUnsignedInt(unsigned int value, unsigned int address) {
  float result;

  asm volatile("lw t3, %0;" : "=m"(address));
  asm volatile("lw t4, %0;" : "=m"(value));

  FOUR_NOPS;
  asm volatile(".word 0x01ce8f53;");
  FOUR_NOPS;

  __asm__ volatile("sw t5, %0;" : "=m"(result));

  return result;
}

float load(unsigned int address) {
  float result;

  asm volatile("lw t3, %0;" : "=m"(address));
  asm volatile("li t4, 0x0;"); // for now this is unused

  FOUR_NOPS;

  asm volatile(".word 0x19ce8f53;");

  FOUR_NOPS;

  __asm__ volatile("sw t5, %0;" : "=m"(result));

  return result;
}

unsigned int loadUnsignedInt(unsigned int address) {
  unsigned int result;

  asm volatile("lw t3, %0;" : "=m"(address));
  asm volatile("li t4, 0x0;"); // for now this is unused

  FOUR_NOPS;

  asm volatile(".word 0x19ce8f53;");

  FOUR_NOPS;

  __asm__ volatile("sw t5, %0;" : "=m"(result));

  return result;
}


unsigned int getMax(unsigned int address) {
  unsigned int result;

  asm volatile("lw t3, %0;" : "=m"(address));
  asm volatile("li t4, 0x0;"); // for now this is unused

  FOUR_NOPS;

  asm volatile(".word 0x11ce8f53");

  FOUR_NOPS;

  __asm__ volatile("sw t5, %0;" : "=m"(result));

  return result;
}