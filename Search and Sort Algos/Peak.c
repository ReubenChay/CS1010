/**
 * CS1010 Semester 2 AY20/21
 * Assignment 7: Peak
 *
 * Finds the peak elevation (if any) of a piece of land. The elevation of a land is given 
 * in an array with each element representing the elevation at every centimetre. It 
 * is guaranteed to either have one peak only or have no peak at all. 
 *
 * @file: peak.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"

/**
 * Finds the peak elevation from an input array which represents the elevation 
 * of a piece of land at every centimetre. 
 *
 * @param[in] list The array which represents the elevations of the piece of land. 
 * @param[in] start The first element of the array which we are checking. 
 * @param[in] end The last element of the array which we are checking. 
 *
 * @pre list is not NULL. 
 * @pre start >= 0 && start < length of array 
 * @pre end >= 0 && end < length of array 
 *
 * @return Returns the index at which the peak elevation is found, and -1 if there 
 * is no peak. 
 */
long find_peak(long *list, long start, long end) {
  if (start >= end) {
    return -1;
  }
  long mid = (start + end) / 2;

  if ((list[mid - 1] < list[mid]) && (list[mid] > list[mid + 1])) { // peak is found
    return mid;
  }

  if ((list[mid - 1] < list[mid]) && (list[mid] < list[mid + 1])) {
    return find_peak(list, mid + 1, end);
    /** elements checked are in increasing order, thus we check
     * to the right side of mid. The oppoisite logic applies to the if-statement
     * below this.
     */
  }

  if ((list[mid - 1] > list[mid]) && (list[mid] > list[mid + 1])) {
    return find_peak(list, start, mid - 1);
  }

  if (find_peak(list, start, mid - 1) == -1) {
    if (find_peak(list, mid + 1, end) != -1) {
      return find_peak(list, mid + 1, end); // peak is on the right side of mid 
    }
  }
  if (find_peak(list, start, mid - 1) != -1) {
    return find_peak(list, start, mid - 1); // peak is on the left side of mid 
  }
  return -1;
}

int main()
{
  long n = cs1010_read_long();
  long *list = malloc((size_t)n * sizeof(long));
  for (long i = 0; i < n; i += 1) {
    list[i] = cs1010_read_long();
  }

  long peak_index = find_peak(list, 0, n - 1);
  if (peak_index == -1) {
    cs1010_println_string("no peak");
  }
  else {
    cs1010_print_long(peak_index);
  }

  free(list);
  return 0;
}
