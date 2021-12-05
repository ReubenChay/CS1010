/**
 * CS1010 Semester 2 AY20/21
 * Assignment 8: Maze
 *
 * Finds the way out of a maze represented in a grid of (m x n) cells, printing the 
 * movement the "character(Scully)" makes as well as the total number of steps 
 * taken before reaching the exit of this maze.
 *
 * @file: maze.c
 * @author: Reuben Chay (Group T07)
 */


#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define EMPTY '.'
#define WALL  '#'
#define USER  '@'

/**
 * Print the maze to the screen.
 * 
 * @param[in] maze The 2D array representing the maze.
 * @param[in] nrows The number of rows of the maze.
 * @param[in] steps The number of steps taken so far.
 */
void print_maze(char **maze, long nrows, long steps) {
  cs1010_clear_screen();
  for (long i = 0; i < nrows; i += 1) {
    cs1010_println_string(maze[i]);
  }
  cs1010_println_long(steps);

  // sleep only if we are displaying in the terminal
  if (isatty(fileno(stdout))) {
    usleep(100*1000);
  }
}

/**
 * Checks if the current cell the user is at is the end cell of the maze.  
 *
 * @param[in] m The total number of rows in the grid
 * @param[in] n The total number of columns in the grid 
 * @param[in] r The current row we are checking 
 * @param[in] c The current column we are checking 
 *
 * @return Returns true if the user is at the end of the maze, false otherwise. 
 */
bool is_end(long m, long n, long r, long c) {
  if ((r == m - 1) || (c == n - 1) || (r == 0) || (c == 0)) {
    return true;
  }
  return false;
}


/**
 * Checks if the the user can move up from the current cell it is at.
 *
 * @param[in] maze The 2D array representing the current state of the maze. 
 * @param[in] r The current row the user is at
 * @param[in] c The current column the user is at 
 *
 * @return Returns true if the user can move up, false otherwise. 
 */
bool can_move_up(char **maze, long r, long c) {
  if (maze[r - 1][c] == EMPTY) {
    return true;
  }
  return false;
}

/**
 * Checks if the the user can move right from the current cell it is at.
 *
 * @param[in] maze The 2D array representing the current state of the maze.
 * @param[in] r The current row the user is at
 * @param[in] c The current column the user is at
 *
 * @return Returns true if the user can move right, false otherwise.
 */
bool can_move_right(char **maze, long r, long c) {
  if (maze[r][c + 1] == EMPTY) {
    return true;
  }
  return false;
}

/**
 * Checks if the the user can move down from the current cell it is at.
 *
 * @param[in] maze The 2D array representing the current state of the maze.
 * @param[in] r The current row the user is at
 * @param[in] c The current column the user is at
 *
 * @return Returns true if the user can move down, false otherwise.
 */
bool can_move_down(char **maze, long r, long c) {
  if (maze[r + 1][c] == EMPTY) {
    return true;
  }
  return false;
}

/**
 * Checks if the the user can move left from the current cell it is at.
 *
 * @param[in] maze The 2D array representing the current state of the maze. 
 * @param[in] r The current row the user is at
 * @param[in] c The current column the user is at 
 *
 * @return Returns true if the user can move left, false otherwise. 
 */
bool can_move_left(char **maze, long r, long c) {
  if (maze[r][c- 1] == EMPTY)  {
    return true;
  }
  return false;
}

/**
 * Finds the starting point of the user, or the '@' character in a given 2D array
 * representing the grid of the maze. 
 *
 * @param[in] maze The 2D array representing the grid of the maze
 * @param[in] m The number of rows in the grid 
 * @param[in] n The number of columns in the grid 
 * @param[out] row The row that the user ('@') is at 
 * @param[out] column The column that the user ('@') is at 
 */
void find_start(char **maze, long m, long n, long *row, long *column) {
  for (long i = 0; i < m; i += 1) {
    for (long k = 0; k < n; k += 1) {
      if (maze[i][k] == USER) {
        *row = i;
        *column = k;
        return;
      }
    }
  }
}

/**
 * Swaps the value of 2 characters. 
 *
 * @param[in, out] x One of the characters we want to swap
 * @param[in, out] y The other of the 2 characters that we want to swap
 *
 * @pre Both x and y have been initialised. 
 */ 
void swap(char *x, char *y) {
  char temp = *x; 
  *x = *y; 
  *y = temp;
}

/**
 * Finds the way out, along with the number of steps taken, of a maze represented by 2D array. 
 *
 * @param[in ,out] maze The 2D array representing the maze. 
 * @param[in, out] temp_maze Another 2D array representing the maze, but in terms of cells that we have visited.
 * @param[in] m The number of rows in maze. 
 * @param[in] n The number of columns in maze. 
 * @param[in] row The row of the  current position of the user ('@') 
 * @param[in] column The row of the current position of the user ('@') 
 * @param[in, out] count The number of step taken. 
 *
 * @pre maze and temp_maze are not NULL. 
 *
 * @return Returns true if the exit of the maze has been found, false if not. 
 *
 */
bool solve_maze(char **maze, char **temp_maze, long m, long n, long row, long column, long *count) {

  if (is_end(m, n, row, column)) {
    return true;
  } 

  temp_maze[row][column] = 'X';

  if (can_move_up(maze, row, column) && can_move_up(temp_maze, row, column)) {
    swap(&maze[row][column], &maze[row - 1][column]);
    (*count) += 1;
    print_maze(maze, m, *count); 
    if (!solve_maze(maze, temp_maze, m, n, row - 1, column, count)) { 
      swap(&maze[row - 1][column], &maze[row][column]);
      (*count) += 1;
      print_maze(maze, m, *count);
    } else {
      return true;
    }
  } 

  if (can_move_right(maze, row, column) && can_move_right(temp_maze, row, column)) {
    swap(&maze[row][column], &maze[row][column + 1]);
    (*count) += 1;
    print_maze(maze, m, *count);
    if (!solve_maze(maze, temp_maze, m, n, row, column + 1, count)) {
      swap(&maze[row][column + 1], &maze[row][column]);
      (*count) += 1;
      print_maze(maze, m, *count);
    } else {
      return true;
    } 
  }

  if (can_move_down(maze, row, column) && can_move_down(temp_maze, row, column)) {
    swap(&maze[row][column],&maze[row + 1][column]);
    (*count) += 1;
    print_maze(maze, m, *count);
    if (!solve_maze(maze, temp_maze, m, n, row + 1, column, count)) {
      swap(&maze[row + 1][column], &maze[row][column]);
      (*count) += 1;
      print_maze(maze, m, *count);
    } else {
      return true;
    }
  } 

  if (can_move_left(maze, row, column) && can_move_left(temp_maze, row, column)) {
    swap(&maze[row][column], &maze[row][column - 1]);
    (*count) += 1;
    print_maze(maze, m, *count);
    if (!solve_maze(maze, temp_maze, m, n, row, column - 1, count)) {
      swap(&maze[row][column - 1], &maze[row][column]);
      (*count) += 1;
      print_maze(maze, m, *count);
    } else {
      return true;
    }
  }

  return false;
}



/**
 * Copies a 2D array to another array of the same size. 
 *
 * @param[in, out] source The array that we want to copy 
 * @param[in, out] destination The array that we want to copy 'source' to 
 * @param[in] m The number of rows in both the arrays. 
 * @param[in] n The number of columns in both the arrays. 
 *
 * @pre Both source and destination are not NULL. 
 */
void copy_array(char **source, char **destination, long m, long n) {
  for (long i = 0; i < m; i += 1) {
    for (long k = 0; k < n; k += 1) {
      destination[i][k] = source[i][k];
    }
  }
}


int main() 
{
  long m = cs1010_read_long();
  long n = cs1010_read_long();
  char **maze = malloc((size_t)m * sizeof(char*));
  for (long i = 0; i < m; i += 1) {
    maze[i] = cs1010_read_word();
  }

  long start_row; 
  long start_column;
  find_start(maze, m, n, &start_row, &start_column);

  char** temp_maze = malloc((size_t)m * sizeof(char*));
  for (long i = 0; i < m; i += 1) {
    temp_maze[i] = malloc((size_t)n * sizeof(char));
  }

  long count = 0;

  copy_array(maze, temp_maze, m, n); 
  solve_maze(maze, temp_maze, m, n, start_row, start_column, &count);

  for (long i = 0; i < m; i += 1) {
    free(maze[i]);
    free(temp_maze[i]);
  }
  free(maze);
  free(temp_maze);

  return 0;

}


