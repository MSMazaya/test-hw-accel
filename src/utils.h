#pragma once
#include <uart.h>

extern void uart_send_char(char c);

void uart_send_float(float num, int max_decimal_places);