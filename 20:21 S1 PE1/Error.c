/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 1: Error
 *
 * @file: error.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

int main()
{
  long k = cs1010_read_long();
  long n = cs1010_read_long(); 

  long i = 1;
  long j = 10;
  long new_number = n;
  while (i <= k) {
    new_number -= new_number % j;
    i += 1;
    j *= 10;
  }

  double error = ((n - new_number) / (double)n) * 100;
    cs1010_print_double(error);
  return 0;
}
