/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 2: Tic-Tac-Toe
 *
 * @file: tictactoe.c
 * @author: XXX (Group Not Needed)
 */
#include "cs1010.h"
#include <stdbool.h>


bool is_diagonal(char grid[][3], char x) {
  if (grid[0][0] == x && grid[1][1] == x && grid[2][2] == x) {
    return true;
  }
  if (grid[2][0] == x && grid[1][1] == x && grid[0][2] == x) {
    return true;
  }
  return false;
}


bool has_won(char grid[][3], char x) {
  if (grid[0][0] == x && grid[0][1] == x && grid[0][2] == x) {
    return true;
  }
  if (grid[1][0] == x && grid[1][1] == x && grid[1][2] == x) {
    return true;
  }
  if (grid[2][0] == x && grid[2][1] == x && grid[2][2] == x) {
    return true;
  }
  if (grid[0][0] == x && grid[1][0] == x && grid[2][0] == x) {
    return true; 
  }
  if (grid[0][1] == x && grid[1][1] == x && grid[2][1] == x) {
    return true;
  }
  if (grid[0][2] == x && grid[1][2] == x && grid[2][2] == x) {
    return true;
  }
  if (is_diagonal(grid, x)) {
    return true;
  }
  return false;
}

int main()
{
  char grid[3][3];
  for (long i = 0; i < 3; i += 1) {
    for (long j = 0; j < 3; j += 1) {
      grid[i][j] = (char)getchar();
    }
    getchar();
  }
  if (has_won(grid, 'X')) { 
    cs1010_println_string("X");
    } else if (has_won(grid, 'O')) {
      cs1010_println_string("O");
      } else {
        cs1010_println_string("no winner");
      }


  return 0;


}
