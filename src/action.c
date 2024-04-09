#include "action.h"

void printAction(int act) {
   switch (act)
   {
   case action_up:
      ee_printf("up\n");
      break;      
   case action_down:
      ee_printf("down\n");
      break;
   case action_left:
      ee_printf("left\n");
      break;
   case action_right:
      ee_printf("right\n");
      break;
   default:
      ee_printf("Invalid action!\n");
      break;
   }
}
