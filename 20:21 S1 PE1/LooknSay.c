/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 1: LookNSay
 *
 * @file: looknsay.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

long next_number(long a) {
  long sum = 0;
  long x = 1;
  long y = 10;
  long n = a % 100000000;
  while (n != 0) {

    long count = 0;
    long digit = n % 10;
    do {
      n /= 10;
      count += 1;
    } while (n % 10 == digit);

    sum += (y * count) + (x * digit);
    x *= 100;
    y *= 100;
  }
  return sum;
}


int main()
{
  long n = cs1010_read_long();
  long k = cs1010_read_long();

  long i = 1;
  long number = n;
  while (i < k) {
    number = next_number(number);
    i += 1;
  }

  cs1010_print_long(number);
  return 0;
    
}
