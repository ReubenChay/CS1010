/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 1: Twilight
 *
 * @file: twilight.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"
#include <stdbool.h>

bool is_astronomical(long hour, long minute) {
  return (((hour == 5) && (minute >= 41)) || ((hour == 6) && (minute <= 5)) || 
    ((hour == 19) && (minute >= 42)) || ((hour == 20) && (minute <= 25)));
}

bool is_nautical(long hour, long minute) {
  return (((hour == 6) && ((minute >= 6) && (minute <= 29))) || ((hour == 19) && ((minute >= 18) && (minute <= 41))));
}

bool is_civil(long hour, long minute) {
  return (((hour == 6) && ((minute >= 30) && (minute <= 50))) || ((hour == 18) && (minute >= 57)) 
      || ((hour == 19) && (minute <= 17)));
}

int main()
{
  long hour = cs1010_read_long();
  long minute = cs1010_read_long();

  if (is_astronomical(hour, minute)) { 
    cs1010_print_string("astronomical");
  } 
  else if (is_nautical(hour, minute)) {
    cs1010_print_string("nautical");
  }
  else if (is_civil(hour, minute)) {
    cs1010_print_string("civil");
  }
  else {
    cs1010_print_string("not twilight");
  }
  return 0;
}
