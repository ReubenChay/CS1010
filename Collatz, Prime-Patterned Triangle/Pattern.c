/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Pattern
 *
 * Read in two positive integers: an interval n (n >= 1) 
 * and the height of the triangle h.  Then draw a triangle
 * according to a given pattern.  
 *
 * @file: pattern.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h> 


bool is_prime(long x) // to check if an input x is a prime number
{
  long i;
  if (x == 1) {
    return true; // print "#" for when the number is 1  
  }

  i = 2;
  while (i <= sqrt(x)) {
    if ( (x % i == 0) && (i != x) ) {
      return false; 
    }
    i += 1; 
  }
  return true;
}

void check_within_cell(long n, long first_number, long row) { // to check if a cell has a prime number within it, given its starting number.
  long i = first_number;
  long primes = 0;
  while (i <= (first_number + ((n - 1) * row))) {
    if (is_prime(i)) {
      primes += 1;
    }
    i += row;
  }
  if (primes >= 1) {
    cs1010_print_string("#"); 
  } else {
    cs1010_print_string(" ");
  }
}



void print_row(long row_no, long height, long n) { // to print individual rows 
  long i;
  long j;
  long k;
  long leading_number = (((row_no * (row_no - 1)) / 2) * n) + 1;

  i = 1;
  while (i <= (height - row_no) ) {
    cs1010_print_string(" ");
    i += 1;
  }

  j = 1;
  while (j <= ((2 * row_no) - 1)) {
    check_within_cell(n, leading_number,row_no);
    j += 1;
    leading_number += 1;
  }

  k = 1;
  while (k < (height - row_no) ) {
    cs1010_print_string(" ");
    k += 1;
  }
  cs1010_println_string(" ");

}

int main()
{
  long n = cs1010_read_long();
  long h = cs1010_read_long();
  long row;

  row = 1;
  while (row <= h) {
    print_row(row, h, n);
    row += 1;
  }

  return 0;



}
