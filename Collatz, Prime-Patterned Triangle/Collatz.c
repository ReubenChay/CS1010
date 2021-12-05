/**
* CS1010 Semester 1 AY20/21
* Assignment 2: Collatz 
*
* Read in a positive integer n from the standard input,
  * then, for each number k between number 1 .. n, transform
  * it into 1 based on the steps below:
  * - if k is even, k = k/2
  * - else, k = 3k + 1
  * Find the number k that requires the most number of steps
  * between 1 and n, and print both k and the number of steps
  * to standard output. If there are multiple numbers with
  * the same number of steps, we prefer to output the larger
  * among these numbers.
  *
  * @file: collatz.c
  * @author: Reuben Chay (Group T07)
  */
#include "cs1010.h"

int main() 
{
  long n = cs1010_read_long(); 
  long steps;
  long max_stopping_time; // indicates highest stopping time thus far
  long max_number; // indicates corresponding number with highest stopping time thus far
  long current_number; 
  long k;


  max_number = 1;
  max_stopping_time = 0;
  for (k = 1; k <= n; k += 1) {

    current_number = k;
    steps = 0;
    while (current_number != 1) {
      if (current_number % 2 == 0) {
        current_number /= 2;
      }
      else {
        current_number *= 3;
        current_number += 1;
      }
      steps += 1;
    }

    if (steps == max_stopping_time) {
      max_number = k;
    }
    if (steps > max_stopping_time) {
      max_stopping_time = steps;
      max_number = k;
    }
  }

  cs1010_println_long(max_number);
  cs1010_print_long(max_stopping_time);

  return 0; 

}
