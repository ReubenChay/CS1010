/**
 * CS1010 Semester 2 AY20/21
 * Assignment 3: CountingSort
 *
 * Read in a series of numbers between 0 and 10000 
 * and sort them using counting sort.
 *
 * @file: countingsort.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"

void count_sort(long list[], long n) {
  long count[10001] = {0};
  for (long i = 0; i < n; i += 1) { // scanning the list[] array and increasing the value of count[x] values whenever x appears in the list[] array.
    count[list[i]] += 1;
  }

  for (long j = 0; j <= 10000; j += 1) {
    if (count[j] > 0) {
      cs1010_print_long(j);
      cs1010_print_string(" ");
      cs1010_println_long(count[j]);
    }
  }

  for (long k = 0; k <= 10000; k += 1) {
    for (long l = 0; l < count[k]; l += 1) { // for a value of k, print it the number of times equal to count[k].
      cs1010_println_long(k);
    }
  }
}

int main()
{
  long n = cs1010_read_long();
  long *list;
  list = cs1010_read_long_array(n);

  count_sort(list, n);
  free(list);
  return 0;
}
