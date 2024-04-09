#pragma once
#include "ee_printf.h"

enum action {
   action_down,
   action_right,
   action_up,
   action_left,
   action_length
};

void printAction(int act);