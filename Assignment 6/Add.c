/**
 * CS1010 Semester 2 AY20/21
 * Assignment 6: Add
 *
 * Adds two non-negative values together to give their sum. 
 * Both the two starting values and their sum are represented as a string 
 * of characters. 
 *
 * @file: add.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"
#include <assert.h>

/**
 * Converts a character into a long value. 
 * 
 * @param[in] x The char we want to convert 
 *
 * @pre The character x is from '0' to '9' 
 *
 * @return Returns the number represented by the character x.
 */
long convert_to_num(char x) {
  long num = x - '0';
  return num;
}

/**
 * Converts a long value into its representative character.
 *
 * @param[in] x The long value we want to convert 
 *
 * @pre x is only an integer from 0 to 9
 *
 * @return Returns the character representing long x.
 */
char convert_to_char(long x) {
  char character = (char)(x + '0');
  return character;
}


/**
 * Sum two integer values represented in the form of strings 
 *
 * @param[in] list1 The first string representing an integer value
 * @param[in] list2 The second string representing an integer value 
 * @param[in] m The length of list1 
 * @param[in] n The length of list2
 * @param[in, out] sumlist The string representing the sum of the 2 integer values 
 *
 * @pre m >= n
 * @pre list1, list2 and sumlist are not NULL 
 *
 */
void sum(char *list1, char *list2, long m, long n, char *sumlist) {
  long carry = 0;
  for (long i = 1; i <= n; i += 1) { // add digits up until the end of the smaller number (if any)
    long a = m - i;
    long b = n - i;
    assert(a >= m - n && a <= m - 1 && b >= 0 && b <= n - 1);
    long sum_of_digit = convert_to_num(list1[a]) + convert_to_num(list2[b]) + carry;
    sumlist[a + 1] = convert_to_char(sum_of_digit % 10);
    carry = sum_of_digit / 10;
  }

  for (long i = m - n - 1; i >= 0; i -= 1) { // add digits of the larger number(if any) after adding the two numbers together 
    assert(i >= 0 && i <= m - n - 1);
    long sum = convert_to_num(list1[i]) + carry;
    sumlist[i + 1] = convert_to_char(sum % 10);
    carry = sum / 10;
  }
  sumlist[0] = convert_to_char(carry);

}


int main() 
{
  char *list1 = cs1010_read_word();
  char *list2 = cs1010_read_word();

  long len1 = (long)strlen(list1);
  long len2 = (long)strlen(list2);

  if (len1 >= len2) {
    long n = len1 + 2; 
    // (len + 2) to account for the possible extra overflow value, and the terminating character '/0'
    char *sumlist = calloc((size_t)n, (size_t)sizeof(char));
    sum(list1, list2, len1, len2, sumlist);

    if (sumlist[0] == '0') {
      cs1010_println_string(sumlist + 1);
    } else {
      cs1010_println_string(sumlist);
    }

    free(sumlist);
  }
  else { 
    long n = len2 + 2;
    char *sumlist = calloc((size_t)n, (size_t)sizeof(char));
    sum(list2, list1, len2, len1, sumlist);
    if (sumlist[0] == '0') {
      cs1010_println_string(sumlist + 1);
    } else {
      cs1010_println_string(sumlist);
    }
    free(sumlist);
  }

  free(list1);
  free(list2);
  return 0;

}


