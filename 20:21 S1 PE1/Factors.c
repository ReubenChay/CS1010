/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 1: Factors
 *
 * @file: factors.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

bool is_prime(long x) {
  if (x == 1) {
    return false;
  }
  if ((x == 2) || (x % 2 == 0)) {
    return true;
  }

  for(long i = 3; i <= sqrt(x); i += 2) {
    if ((x % i == 0) && (i != x)) {
      return false;
    }
  }
  return true;
}

long division(long n, long prime_factor) {
  long count = 0;
  while (n % prime_factor == 0) {
    n /= prime_factor;
    count += 1;
  }

  if (count > 0) {
  cs1010_print_long(prime_factor);
  cs1010_print_string(" ");
  cs1010_println_long(count);
  }
  return n;
}

void prime_factorisation(long n) {
  long i = 2;
  while (n != 1) {
    if (is_prime(i)) {
      n = division(n, i);
    }
    i += 1;
  }
}

int main()
{
  long n = cs1010_read_long();
  prime_factorisation(n);
  return 0;
}
