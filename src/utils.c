#include "utils.h"

void uart_send_float(float num, int max_decimal_places) {
    // Print integer part of the float
    int integer_part = (int)num;
    uart_send_char((char)(integer_part + '0'));

    // Print the decimal point
    uart_send_char('.');

    // Handle negative numbers
    if (num < 0) {
        num = -num;
        integer_part = -integer_part;
    }

    // Print decimal part up to max_decimal_places
    float decimal_part = num - integer_part;
    for (int i = 0; i < max_decimal_places; ++i) {
        decimal_part *= 10;
        int digit = (int)decimal_part;
        uart_send_char((char)(digit + '0'));
        decimal_part -= digit;
    }
}
