/**
 * CS1010 Semester 2 AY20/21
 * Assignment 7: Inversion
 *
 * Finds the number of inversions in an array of 'n' numbers which is increasing for 
 * the first k numbers (0 <= k <= n) then decreasing for the remaining numbers in the array.
 *
 *
 * @file: inversion.c
 * @author: Reuben Chay (Group T07)
 */

#include "cs1010.h"

/**
 * Finds the "peak" of an array of numbers (if any). The array's first k numbers (0 <= k <= n) are 
 * in increasing order, and the remaining numbers are in decreasing order. The "peak" is the highest 
 * number in the whole array, given that the array k >= 1. 
 *
 * @param[in] list The array that we are scanning through.
 * @param[in] n The length of the array. 
 *
 * @pre list is not NULL. 
 *
 * @return Returns the index of the peak, if any. Otherwise, returns -1 if the array is arranged 
 * in decreasing order, and -2 if it is arranged in increasing order.
 */
long find_peak(long *list, long n) { 
  for (long i = 1; i < n - 1; i += 1) {
    if ((list[i - 1] < list[i]) && (list[i] > list[i + 1])) {
      return i;
    }
  }
  // to execute the statements below, no peak has been found above. 
  if (list[0] > list[n - 1]) {
    return -1; // return -1 if the array is in decreasing order 
  }  
  return -2; // return -2 if the array is already in increasing order
}


/**
 * Finds the number of inversions in an array which first k numbers (0 <= k <= n) are in increasing order
 * and the subsequent numbers are in decreasing order. 
 *
 * @param[in] list The list that we are checking. 
 * @param[in] n The length of the array. 
 * @param[in] peak The index containing the peak number in the array.
 *
 * @pre list is not NULL.
 * @pre list contains a peak number. 
 *
 * @return Returns the number of inversions in the array.
 */
long inversions(long *list, long n, long peak) {
  long count = 0;
  long end = n - 1;
  long count1 = ((end - peak) * (end - peak - 1)) / 2; // all numbers in the decreasing portion of the array are inversed. 
  long start = 0;
  while ((start <= peak) && (end >= peak + 1)) {
    if (list[start] > list[end]) { 
      long num = peak - start + 1;
      /**
       * If list[start] > list[end], then all the numbers from list[start] to list[peak] will be more than list[end] as well, hence
       * all of them will be inversed. 
       */
      count += num;
      end -= 1;
    }
    if (list[start] < list[end]) {
      start += 1;
    }
  }
  count += count1;
  return count;
}


int main()
{
  long n = cs1010_read_long();
  long *list = malloc((size_t)n * sizeof(long));
  for (long i = 0; i < n; i += 1) {
    list[i] = cs1010_read_long();
  }

  long max_index = find_peak(list, n);

  if (max_index == -1) {
    long inversions = (n * (n - 1)) / 2; // array is in decreasing order, inversions = max number of pairs. 
    cs1010_println_long(inversions);
  }
  else if (max_index == -2) {
    cs1010_println_long(0); // array is in increasing order, there is no inversion.
  } else {
    cs1010_println_long(inversions(list, n, max_index));
  }

  free(list);
  return 0;


}
