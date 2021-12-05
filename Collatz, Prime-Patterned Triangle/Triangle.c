#include "cs1010.h"
/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Triangle
 *
 * Read in a positive integer h from standard input and 
 * print an equlateral triangle of height h.
 *
 * @file: triangle.c
 * @author: Reuben Chay (Group T07)
 */



void print_row(long row_number, long height) {
  long i;
  long j;
  long k;

  i = 1;
  while (i <= (height - row_number)) {
    cs1010_print_string(" ");
    i += 1;
  }

  j = 1;
  while (j <= ((2 * row_number) - 1)) {
    cs1010_print_string("#");
    j += 1;
  }

  k = 1; 
  while (k < (height - row_number)) {
    cs1010_print_string(" ");
    k += 1;
  }
  cs1010_println_string(" ");
}

int main()
{
  long h = cs1010_read_long();
  long i; // i denotes row number.

  i = 1;
  while (i <= h) {
    print_row(i, h);
    i += 1;
  }

  return 0;
}
