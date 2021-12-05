/**
 * CS1010 Semester 2 AY20/21
 * Assignment 7: Sort
 *
 * Sort an array of n numbers in increasing order, of which the input array
 * is increasing for its first k numbers (0 <= k <= n) and 
 * then decreasing for the rest of the subsequent numbers. 
 *
 * @file: sort.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"
#include <assert.h>

/**
 * Copies an array of 'len' numbers from the source array to a destination array.
 *
 * @param[in, out] source The array which we are copying from. 
 * @param[in, out] destination The array which we are copying to.
 * @param[in] len The length of the two arrays. 
 *
 * @pre Both arrays are not NULL.
 */
void copy_array(long *source, long *destination, long len) {
  for (long i = 0; i < len; i += 1) {
    destination[i] = source[i];
  }
}

/**
 * Sorts an array of 'n' numbers which is increasing for its first k numbers (0 <= k <= n) 
 * then decreasing for the remaining numbers. 
 *
 * @param[in, out] list The array which we want to sort in increasing order. 
 * @param[in] n The length of the array we want to sort. 
 *
 * @pre list is not NULL. 
 */
void sort_array(long *list, long n) {
  long *temp = malloc((size_t)n * sizeof(long));
  long start = 0;
  long end = n - 1;
  long i = 0;
  while (start <= end) {
    assert(i >= 0 && i < n);
    assert(start >= 0 && end >= 0 && start < n && end < n);
    if (list[start] < list[end]) {
      temp[i] = list[start];
      start += 1;
      i += 1;
    }
    if (list[start] > list[end]) {
      temp[i] = list[end];
      end -= 1;
      i += 1;
    }
    if (list[start] == list[end]) {
      temp[i] = list[start];
      start += 1;
    }
  }

  copy_array(temp, list, n);
  free(temp);
}

/**
 * Prints an array to the screen. 
 *
 * @param[in] list The array which we want to print. 
 * @param[in] n The length of this array. 
 *
 * @pre list is not NULL. 
 */
void print_array(long *list, long n) {
  for (long i = 0; i < n; i += 1) {
    cs1010_print_long(list[i]);
    cs1010_print_string(" ");
  }
}


int main()
{
  long n = cs1010_read_long();
  long *list = malloc((size_t)n * sizeof(long));
  for (long i = 0; i < n; i += 1) {
    list[i] = cs1010_read_long();
  }

  sort_array(list, n);
  print_array(list, n);

  free(list);
  return 0;
}
