/**
 * CS1010 Semester 1 AY20/21
 * Practical Exam 2: Substring
 *
 * @file: substring.c
 * @author: XXX (Group Not Needed)
 */
#include "cs1010.h"


void print_substrings(char *string, char* temp, long start, long k, long len, long count) {
  if (count == k) { 
    cs1010_println_string(temp);
    return;

    // count denotes the number of characters we have inputted, and we only want k characters 
  }

  for (long i = start; i <= len - k + count; i += 1) {
    temp[count] = string[i];
    print_substrings(string, temp, i + 1, k, len, count + 1);
    // this loop fixes the first char position then calls a recursive function, and puts the first char
    // into temp[i]inside that function
    // it then fixes the next element (start + 1) and so on. We fix the indexes of these characters
    // and in a sense, permute the rest. We then do this up till the index with len - k
  }
}

int main() {
  char *string = cs1010_read_word(); 
  long k = cs1010_read_long();
  long n = (long)strlen(string);
  char *temp = calloc((size_t)k+1, sizeof(char));
  print_substrings(string, temp, 0, k, n, 0);

  free(temp);
  free(string);
}

