/**
 * CS1010 Semester 2 AY20/21
 * Assignment 5: Social
 *
 * Reads in the social network of n persons, along with the degree of separation k. 
 * Outputs the social networking of these n persons based on degree k.
 *
 * @file: social.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"
#include <stdbool.h>

/**
 *
 * Checks if two characters are both '1' 
 *
 * @param[in] a One of the 2 characters 
 * @param[in] b The other of the 2 characters
 *
 * @return Returns true if both the characters are '1', false otherwise 
 */
bool is_both_one(char a, char b) {
  return ((a == '1') && (b == '1'));
}


/**
 * Checks if there is indirect contact between 2 persons, m and n, at varying 
 * degrees of separation (k). 
 * In short, this function checks two arrays, one representing the contact traces at 
 * separation degree of k = 1, the other representing  another value of separation degree "x".
 * Then, it makes the neccessary changes to the cell that is checked (represented by m and n).
 *
 * @param[in] list The array representing separation degree x
 * @param[in] list1 The array representing separation  degree 1.
 * @param[in] m The ID of one of the 2 persons we are checking. 
 * @param[in] n The ID of the other of the 2 persons we are checking. 
 * @param[in, out] newlist The array which represents separation  degree (x + 1)
 * for the cells that are being checked.
 *
 * @pre list, list1 and newlist are not NULL 
 *
 */
void is_indirect_contact(char **list, char **list1, long m, long n, char **newlist) {
  long i = m + 1;
  while (i <= n - 1) {
    if (is_both_one(list[i][m], list1[n][i])) {
      if (n > m) {
        newlist[n][m] = '1';
      } else {
        newlist[m][n] = '1';
      }
    }
    i += 1;
  }
}


/**
 * Copies a 2D array to another array (ie. from source to destination)
 *
 * @param[in] source The 2D array which we want to copy
 * @param[in,out] destination The 2D array which we want to copy 'source' to
 * @param[in] n The number of rows in the source array
 *
 * @pre Both 'source' and 'destination' are not NULL
 */
void copy_grid(char **source, char **destination, long n) {
  for(long i = 0; i < n; i += 1) {
    for (long j = 0; j <= i; j += 1) {
      destination[i][j] = source[i][j];
    }
  }
}


/**
 * Given an array representing a separation degree of x, it makes the neccessary 
 * changes such that the new array represents the separation degree of x + 1.
 * 
 * @param[in, out] list The array representing separation  degree x, and later 
 * degree of (x + 1)
 * @param[in] list1 The array representing separation degree 1.
 * @param[in] n The number of persons
 *
 * @pre list and list1 are not NULL.
 *
 */
void new_array(char **list, char **list1, long n) {
  char **newlist = malloc((size_t)n * sizeof(char*));
  for (long i = 0; i < n; i += 1) {
    newlist[i] = malloc((size_t)(i + 1) * sizeof(char*));
  }
  copy_grid(list, newlist, n);
  for (long i = 0; i < n - 1; i += 1) {
    for (long k = i + 1; k < n; k += 1) {
      is_indirect_contact(list, list1, i, k, newlist);
    }
  }
  copy_grid(newlist, list, n);

  for(long i = 0; i < n; i += 1) {
    free(newlist[i]);
  }
  free(newlist);

}



/**
 * Given a 2D array, prints it to the screen
 *
 * @param[in] list The given 2D array
 * @param[in] n The number of rows in the 2D array
 *
 * @pre list is not NULL
 *
 */
void print_array(char **list, long n) {
  for (long i = 0; i < n; i += 1) {
    for (long k = 0; k <= i; k += 1) {
      putchar(list[i][k]);
    }
    cs1010_println_string("");
  }
}



int main()
{
  long n = cs1010_read_long();
  long k = cs1010_read_long();
  char **list1 = malloc((size_t)n * sizeof(char*));
  for (long i = 0; i < n; i += 1) {
    list1[i] = cs1010_read_word();
  }

  char **list = malloc((size_t)n * sizeof(char*));
  for(long i = 0; i < n; i += 1) {
    list[i] = malloc((size_t)(i + 1) * sizeof(char));
  }


  copy_grid(list1, list, n);

  if (k == 1) { 
    print_array(list1, n);
  } else {
    for (long j = 1; j < k; j += 1) {
      new_array(list, list1, n);
    }
    print_array(list, n);
  }

  for(long i = 0; i < n; i += 1) {
    free(list1[i]);
    free(list[i]);
  }
  free(list1);
  free(list);

  return 0;



}
