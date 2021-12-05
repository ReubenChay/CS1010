/**
 * CS1010 Semester 2 AY20/21
 * Assignment 4: SelectionSort
 *
 * TODO: Write documentation
 *
 * @file: selectionsort.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"

/**
 * To swap two long variables
 *
 * param[in,out] a The first variable that we are swapping 
 * param[in,out] b The second variable that we are swapping
 */
void swap(long *a, long *b) {
  long temp = *a;
  *a = *b;
  *b = temp; 
} 


/**
 * Finds the element of the maximum value within a restricted range of an array (from 0 to length). 
 * Then, if this largest element is not already in the position of list[length], the largest element
 * is swapped with the element in the position of list[length]. 
 *
 * @param[in,out] list The array of numbers we are aiming to sort.
 * @param[in] length The constraint of where we scan the array up till to check for maximum value. 
 *
 * @pre Each number in the array is unique ie. There are no repeated numbers
 *
 */
void swap_max_and_last(long list[], long length) { 
  long max_so_far = list[0];
  long max_element = 0;
  for (long i = 1; i <= length; i += 1) {
    if (list[i] > max_so_far) {
      max_so_far = list[i];
      max_element = i;
    }
  }
  if (max_element != length) { // to ensure that the program only swaps the elements if the current max is not the last element checked.
    swap(&list[max_element], &list[length]);
  }
}


/**
 * To print the elements of an array in sequential order.
 *
 * @param[in,out] list The array that we want to print the elements from. 
 * @param[in] length The length of the array.
 *
 */
void print_array(long list[], long length) {
  for (long i = 0; i < length; i += 1) {
    cs1010_print_long(list[i]);
    cs1010_print_string(" ");
  }
  cs1010_println_string("");
}


int main() 
{
  long n = cs1010_read_long();
  long *list = cs1010_read_long_array(n);
  if (list == NULL) {
    return 1;
  }

  for (long i = n - 1; i > 0; i -= 1) { // repeatedly call the "find max then swap" function, while checking for a smaller range of the array at each iteration.
    swap_max_and_last(list, i);
    print_array(list, n);
  }

  free(list);
  return 0;

}
