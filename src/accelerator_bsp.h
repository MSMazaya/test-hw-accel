#pragma once
#define FOUR_NOPS asm volatile("nop;nop;nop;nop;")

typedef enum _ConstantType {
  CONSTANT_TYPE_LEARNING_RATE,
  CONSTANT_TYPE_DISCOUNT_FACTOR,
  CONSTANT_TYPE_NEXT_STATE
} ConstantType;

void setConstant(ConstantType mode, float value);
void setNextState(unsigned int next_state);
float qUpdate(unsigned int q_table_address, float reward);
float storeQValue(float value, unsigned int address);
float storeUnsignedInt(unsigned int value, unsigned int address);
float load(unsigned int address);
unsigned int loadUnsignedInt(unsigned int address);
unsigned int getMax();