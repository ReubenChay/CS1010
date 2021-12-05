/**
 * CS1010 Semester 2 AY20/21
 * Assignment 6: Permutation
 * 
 * Given two strings of lowercase letters 'a' to 'z', with 
 * first string * no longer than the second. This program 
 * checks if the 1st string is a permutation of a substring 
 * of the 2nd one.
 *
 * @file: permutation.c
 * @author: Reuben Chay (Group T07))
 */
#include "cs1010.h" 
#include <stdbool.h>
#include <assert.h>


/**
 * Checks if 2 strings of characters  of the same length are anagrams of each other. 
 *
 * @param[in] list1 The first list we are checking. 
 * @param[in] list2 The second list we are checking. 
 * @param[in] k The length of both list1 and list2. 
 * 
 * @pre Both list1 and list2 are not NULL
 *
 * @return Returns true if the 2 strings of characters are anagrams, false otherwise.
 *
 */
bool is_anagram(char *list1, char *list2, long k) {
  for (long i = 0; i < k; i += 1) {
    assert(i >= 0 && i < k);
    if (list1[i] != list2[i]) {
      return false;
    }
  }
  return true;
}

/**
 * Given a string of k characters and a string of n characters (k <= n), determines if 
 * the string of k characters is an anagram to a substring of the string with n characters.
 * This can be described as the list of k characters being a substring permutation of the list
 * with n characters. 
 *
 * @param[in] s1 The string with k characters (shorter string). 
 * @param[in] s2 The string with n characters (longer string).
 *
 * @pre s1 and s2 are not NULL. 
 *
 * @return Returns true if s1 is a substring permutation of the string s2, false otherwise.
 */
bool is_substring_permutation(char *s1, char *s2) {
  long k = (long)strlen(s1);
  long n = (long)strlen(s2);

  char count_s1[26] = {0}; 
  char count_s2_substring[26] = {0};
  // both arrays above represents the frequency of each letter 'a' to 'b', represented as [0] to [25] in the strings.

  for (long i = 0; i < k; i += 1) { 
    assert(i >= 0 && i < k);
    count_s1[s1[i] - 'a'] += 1;
    count_s2_substring[s2[i] - 'a'] += 1;
  }

  /**
   * After setting the substring of s2 to the first k characters, we begin comparing this substring
   * to s1 to see if they are anagrams of each other. Then, we traverse across s2 to form new 
   * substrings which we continue comparing against s1 if it doesn't return true. 
   */

  long i = k;
  while (i < n) {
    if (is_anagram(count_s1, count_s2_substring, 26)) {
      return true;
    }
    assert(i >= k && i < n);
    count_s2_substring[s2[i] - 'a'] += 1; 
    count_s2_substring[s2[i - k] - 'a'] -= 1;
    i += 1;
  }
  return false;
}

int main()
{
  char *s1 = cs1010_read_word(); // string of k characters 
  char *s2 = cs1010_read_word(); // string of n characters
  if (is_substring_permutation(s1, s2)) {
    cs1010_println_string("YES");
  }
  else { 
    cs1010_println_string("NO");
  }
  free(s1);
  free(s2);
  return 0;

}
