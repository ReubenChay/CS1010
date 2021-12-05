/**
 * CS1010 Semester 2 AY20/21
 * Assignment 8: Walk
 *
 * Assuming a city laid out in a grid of its building blocks, this program takes in
 * the block we want to go to, 'x' blocks to the east and 'y' blocks to the north. 
 * It returns the number of different paths one can take to reach his/her 
 * destination, assuming his starting position his at (0,0) and the destination is (x,y). 
 *
 * @file: walk.c
 * @author: Reuben Chay (Group T07))
 */
#include "cs1010.h"

/**
 * Creates a 2D array representing the total number of ways to 
 * reach each cell from the position of (0,0) ie. grid[0][0]. 
 *
 * @param[in, out] grid The 2D array we will create this matrix on. 
 * @param[in] rows The number of rows in the 2D array.
 * @param[in] columns The number of columns in the 2D array. 
 *
 * @pre grid is not NULL. 
 *
 */
void get_matrix(long **grid, long rows, long columns) {
  for (long i = 0; i < rows; i += 1) {
    grid[i][0] = 1;
  }
  for (long i = 0; i < columns; i += 1) {
    grid[0][i] = 1;
  }
  // there is only one way to get the the border cells

  for (long i = 1; i < rows; i += 1) {
    for (long k = 1; k < columns; k += 1) {
      grid[i][k] = grid[i - 1][k] + grid[i][k - 1];
      /** for each subsequent cell, the number of ways to get to it is the sum of 
       * the number of ways to get to the cells above it and to its left. 
       */
    }
  }
}

int main() 
{
  long x = cs1010_read_long();
  long y = cs1010_read_long(); 

  long rows = y + 1;
  long columns = x + 1;
  // represented as a 2D array, there will be 1 more of row/column than x/y. 

  long **grid = malloc((size_t)rows * sizeof(long*));
  for (long i = 0; i < rows; i += 1) {
    grid[i] = malloc((size_t)columns * sizeof(long));
  }

  get_matrix(grid, rows, columns); 

  cs1010_println_long(grid[y][x]);
  /** from the matrix representing number of ways to get to a cell from grid[0][0],
   *  the very last cell (grid[y][x]) represents the total number of ways 
   *  to get from (0,0) to (y,x).
   */

  for (long i = 0; i < rows; i += 1) {
    free(grid[i]);
  }
  free(grid);
  return 0;

}
