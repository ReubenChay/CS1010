/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 1: Reverse
 *
 * @file: reverse.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"
#include <math.h>

long digits(long n) {
  if (n / 10 == 0) {
    return 1;
  }
    return (1 + digits(n / 10));
}

long square_of(long x) {
  return x * x;
}

long reverse_number(long n, long digit) {
  long power = pow(10, digit);
  if (n / 10 == 0) {
    return n;
  }
  return (power * (n % 10) + reverse_number(n / 10, digit - 1));

}

int main()
{
  long n = cs1010_read_long();
  long new_number = reverse_number(n, digits(n) - 1);
  long output = square_of(new_number);
  cs1010_print_long(output);
  return 0;
}
