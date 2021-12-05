/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Prime
 *
 * Reads in an integer n from standard input and print 
 * the largest prime smaller or equal to n.
 *
 * @file: prime.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

bool is_prime(long x) 
{
  long k;

  if (x == 1) {
    return false;
  }
  k = 2;
  while (k <= sqrt(x)) {
    if ( (x % k == 0) && (k != x) ) {
      return false;
    }
    k += 1;
  }
  return true;
}

int main()
{
  long n = cs1010_read_long();
  long i;
  long largest_prime;

  i = n;
  while (i >= 1) {
    if (is_prime(i)) {
      largest_prime = i;
      i = 1;
    }
    i -= 1;
  }

  cs1010_print_long(largest_prime); 
  return 0; 

}
