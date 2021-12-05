/**
 * CS1010 Semester 2 AY20/21
 * Assignment 6: Frequency
 * 
 * Given 2 equal length string of small letter 'a' 
 * to 'z', this program checks if both have the
 * same set of alphabets appearing the same number
 * of time.
 *
 * @file: frequency.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"
#include <stdbool.h>
#include <assert.h>

/**
 * Checks if 2 strings of characters, which are of the same length, are anagrams of each other.
 *
 * @param[in] list1 The first string we are checking.
 * @param[in] list2 The second list we are checking. 
 * @param[in] len The length of both the strings. 
 *
 * @pre list1 and list2 are not NULL.
 *
 * @return Returns true if both the strings are anagrams of each other, false otherwise. 
 */
bool is_both_anagrams(char *list1, char *list2, long len) {
  char count1[26] = {0};
  char count2[26] = {0};
  // count1 and count2 represents the frequency of each letter 'a' to 'z', represented as [0] to [25] in the strings.

  for (long i = 0; i < len; i += 1) {
    assert(i >= 0 && i < len);
    count1[list1[i] - 'a'] += 1;
    count2[list2[i] - 'a'] += 1;
  }

  for (long i = 0; i < 26; i += 1) {
    assert(i >= 0 && i < 26);
    if (count1[i] != count2[i]) { // as long as the frequency of each letter does not tally, then they are not anagrams.
      return false;
    }
  }
  return true;
}

int main()
{
  char *list1 = cs1010_read_word();
  char *list2 = cs1010_read_word();
  long len = (long)strlen(list1);

  if (is_both_anagrams(list1, list2, len)) {
    cs1010_println_string("YES");
  } else {
    cs1010_println_string("NO");
  }
  free(list1);
  free(list2);
  return 0;

}

