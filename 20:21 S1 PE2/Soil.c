/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 2: Soil
 *
 * @file: soil.c
 * @author: XXX (Group Not Needed)
 */
#include "cs1010.h"
#include <assert.h>

void find_grid(long **grid, long search, long m, long n) {
  long row = m - 1;
  long column = 0;
  while (column <= n - 1 && row >= 0) {
    assert(row <= m - 1 && row >= 0);
    assert(column <= n - 1 && column >= 0);
    if (grid[row][column] == search) {
      cs1010_print_long(row); 
      cs1010_print_string(" ");
      cs1010_println_long(column);
      return;
    }
    if (search < grid[row][column]) {
      row -= 1;
    } else if (search > grid[row][column]) { // else is neccessary, if you do 2 if statements then we might accesss out of bounds 
      column += 1;
    }
  }
  cs1010_println_string("not found");
}




int main()
{
  long m = cs1010_read_long();
  long n = cs1010_read_long();
  long k = cs1010_read_long(); 

  long **grid = malloc((size_t)m * sizeof(long*));
  for (long i = 0; i < m; i += 1) {
    grid[i] = cs1010_read_long_array(n);
  }

  for (long i = 1; i <= k; i += 1) {
    long search = cs1010_read_long(); 
    find_grid(grid, search, m, n);
  }

  for (long i = 0; i < m; i += 1) {
    free(grid[i]);
  }
  free(grid);
  return 0;
}
