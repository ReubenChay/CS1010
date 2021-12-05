/**
 * CS1010 Semester 2 AY20/21
 * Assignment 3: Max
 *
 * Read in a sequence of numbers and recursively find
 * the maximum.
 *
 * @file: max.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"

long higher_of(long x, long y) {
  if (x > y) {
    return x;
  } 
  return y;
}

long max(const long list[], long start, long end) {
  if (end == start) { // base case is when we halve the array repeatedly until there is one element left.
    return list[start];
  }

  return higher_of(max(list, start, (start + end) / 2), max(list, ((start + end) / 2) + 1, end));
  // if there are > 1 elements in the array, we continue to halve it.
}


int main()
{
  long n = cs1010_read_long(); 
  long* list = cs1010_read_long_array(n);
  long max_number =  max(list, 0, n - 1);

  cs1010_print_long(max_number);
  free(list);
  return 0;
}
