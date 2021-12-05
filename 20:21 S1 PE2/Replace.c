/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 2: Replace
 *
 * @file: replace.c
 * @author: XXX (Group Not Needed)
 */
#include "cs1010.h"
#include <stdbool.h>

void copy_array(char *source, char *destination, long len) {
  for (long i = 0; i < len; i += 1) {
    destination[i] = source[i];
  }
}


bool is_same_string(char *string, char *search_for, long len1, long start) {
  long end = start + len1;
  long k = 0;
  for (long i = start; i < end; i += 1) {
    if (string[i] != search_for[k]) {
      return false;
    }
    k += 1;
  }
  return true;
}


void replace(char *string, char *s1, char *s2) {
  long n = (long)strlen(string) + 1;
  long len1 = (long)strlen(s1);
  long len2 = (long)strlen(s2);
  char *newstring = calloc((size_t)n, sizeof(char));

  long start = 0;
  long i = 0; 
  while (start <= n - len1) {
    if (!is_same_string(string, s1, len1, start)) {
      newstring[i] = string[start];
      i += 1;
      start += 1;
    }

    if (is_same_string(string, s1, len1, start)) {
      long a = 0; 
      while (a < len2) {
        newstring[i] = s2[a];
        i += 1;
        a += 1;
      }
      start += len1; 
    }
  }

  while (start <= n) {
    newstring[i] = string[start]; 
    i += 1; 
    start += 1;
  }

  copy_array(newstring, string, n);
  free(newstring);
}


int main()
{
  char *string = cs1010_read_word();
  long n = (long)strlen(string);
  long k = cs1010_read_long();
  
  for (long i = 1; i <= k; i += 1) {
  char *s1 = cs1010_read_word(); // substring to find 
  char *s2 = cs1010_read_word(); // replacement string
  replace(string, s1, s2);
  }

  cs1010_println_string(string);

  free(string);


}
