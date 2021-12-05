/**
 * CS1010 Semester 2 AY20/21
 * Assignment 5: Life
 *
 * Simulates the Game of Life. Reads in 3 integers n (> 2)and m (>2), which corresponds to 
 * the number of rows and columns in a 2D grid, along with k, which represents the number of 
 * iterations. Prints to the screen a n x m grid of "#" and "." which represent alive and
 * dead cells, for k times, each team changing according to the rules of the game. 
 *
 * @file: life.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"
#include <stdbool.h>

/**
 * Given a 2D array, prints it to the screen 
 *
 * @param[in] list The given 2D array representing the present grid
 * @param[in] row The number of rows in the 2D array 
 * @param[in] column The number of columns in the 2D array 
 *
 * @pre list is not NULL
 *
 */
void print_grid(char **list, long row, long column) {
  for (long i = 0; i < row; i += 1) {
    for (long k = 0; k < column; k += 1) {
      putchar(list[i][k]);
    }
    cs1010_println_string("");
  }
}


/**
 * For a given cell in the 2D array (ie. list[a][b]), check how many live neighbours it has (ie. number of '#' in its surrounding cells)
 *
 * @param[in] list The given 2D array representing the present grid 
 * @param[in] row The row number of the cell we want to check
 * @param[in] column The column number of the cell we want to check 
 *
 * @pre list is not NULL
 *
 * @return Returns the number of "live neighbours" surrounding a particular cell
 *
 */
long num_of_live_neighbours(char **list, long row, long column) {
  long count = 0;

  /**
   * Given the cell list[row][column], 
   * the first loop checks for the cells in the row above 
   * the second loop checks for the cells in the row below 
   * the last two if statements checks the cells to its left and right
   * After this, we have checked the 8 cells surrounding list[row][column]
   */

  for (long i = column - 1; i <= column + 1; i += 1) { 
    if (list[row - 1][i] == '#') {
      count += 1;
    }
  }
  for (long k = column - 1; k <= column + 1; k += 1) {
    if (list[row + 1][k] == '#') {
      count += 1;
    }
  }
  if (list[row][column - 1] == '#') {
    count += 1;
  }
  if (list[row][column + 1] == '#') {
    count += 1;
  }
  return count;
}


/** 
 * Copies a 2D array to another array (ie. from source to destination) 
 *
 * @param[in] source The 2D array which we want to copy
 * @param[in,out] destination The 2D array which we want to copy 'source' to
 * @param[in] n The number of rows in the source array
 * @param[in] m The number of columns in the source array
 *
 * @pre Both 'source' and 'destination' are not NULL
 */
void copy_grid(char **source, char **destination, long n, long m) {
  for (long i = 0; i < n; i += 1) {
    for (long j = 0; j < m; j += 1) {
      destination[i][j] = source[i][j];
    }
  }
}


/**
 * Changes the given 2D array representing the grid according to the rules of the game
 *
 * @param[in, out] list The 2D array representing the current grid which we want to change 
 * @param[in] n The number of rows in the 2D array 
 * @param[in] m The number of columns in the 2D array
 *
 * @pre list is not NULL 
 *
 */
void change_grid(char **list, long n, long m) {
  char **copy = malloc((size_t)n * sizeof(char*));
  for (long j = 0; j < n; j += 1) {
    copy[j] = malloc((size_t)m * sizeof(char));
  }

  copy_grid(list, copy, n, m); // a temporary copy of the array is made to make changes to, so that we can retain the original array to continue comparing.
  for (long i = 1; i < n - 1; i += 1) { 
    for (long k = 1; k < m - 1; k += 1) { // this nested loop, along with the outer loop, checks all the cells systematically, excluding the border cells.
      long count = num_of_live_neighbours(list, i, k);
      if (list[i][k] == '.') {
        if (count == 3) {
          copy[i][k] = '#';
        }
      }
      else if (list[i][k] == '#') {
        if (count < 2) {
          copy[i][k] = '.';
        }
        if (count > 3) {
          copy[i][k] = '.';
        }
      }
    }
  }
  copy_grid(copy, list, n, m); 

  for(long i = 0; i < n; i += 1) {
    free(copy[i]);
  }
  free(copy);
}



int main()
{
  long n = cs1010_read_long();
  long m = cs1010_read_long();
  long k = cs1010_read_long();
  char **list = malloc((size_t)n * sizeof(char*));
  for (long i = 0; i < n; i += 1) {
    list[i] = cs1010_read_word();
  }

  for (long j = 1; j <= k; j += 1) {
    cs1010_clear_screen();
    change_grid(list, n, m);
    print_grid(list, n, m);
  }

  for (long i = 0; i < n; i += 1) {
    free(list[i]);
  }
  free(list);

  return 0;

}
