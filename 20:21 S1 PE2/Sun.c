/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 2: Sun
 *
 * @file: sun.c
 * @author: XXX (Group Not Needed)
 */
#include "cs1010.h"
#include <stdbool.h> 
#include <math.h>


bool is_prime(long x) {
  if (x == 1) {
    return false;
  }

  for (long i = 2; i <= sqrt(x); i += 1) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

long find_tri_num(long x) {
  long max = 1; 
  long tri = 0;
  while (tri <= x) {
    tri = (max * (max + 1)) / 2;
    max += 1;
  }
  return max;
}


int main() {
  long n = cs1010_read_long();

  long max = find_tri_num(n);

  for (long i = max - 2; i >= 0; i -= 1) {
    long triangular = (i * (i + 1)) / 2;
    if (is_prime(n - triangular)) {
      cs1010_print_long(n - triangular);
      cs1010_print_string(" ");
      cs1010_println_long(triangular);
    }
  }
  return 0;
}
