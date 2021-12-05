/**
 * CS1010 Semester 2 AY20/21
 * Assignment 5: Contact
 *
 * Given a list of n persons and their respective contact traces with the other persons from the 
 * list, along with the IDs of 2 individuals from this list, returns whether they had "direct 
 * contact" with each other, "indirect contact" with each other (through another person from 
 * the list), or "no contact" at all (neither direct nor indirect contact). 
 *
 * @file: contact.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"
#include <stdbool.h>

/**
 * Checks if there is direct contact between person n and person m.
 *
 * @param[in] list The contact traces of all persons give represented in a 2D array
 * @param[in] m The ID of One of the two persons we are checking 
 * @param[in] n The ID of the other of the two persons we are checking 
 *
 * @pre List is not NULL.
 * @return Returns true if there is direct contact between person m and n, false otherwise
 */
bool is_direct_contact(char **list, long m, long n) {
  return (list[n][m] == '1');
}


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
 * 
 * Checks if there is indirect contact (contact through an intermeadiate person) between persons m and n
 *
 * @param[in] list The contact traces of all persons given represented in a 2D array
 * @param[in] m The ID of one of the 2 persons we are checking 
 * @param[in] n The ID of the other of the 2 persons we are checking
 * @param[out] a The ID of the intermeadiate person between persons m  and n
 *
 * @return Returns true if there is indirect contact between persons m and n, false otherwise
 */
bool is_indirect_contact(char **list, long m, long n, long *a) {
  long i = m + 1;
  while (i <= n - 1) { 
    if (is_both_one(list[i][m], list[n][i])) { // for one of the persons, check his/her row, then check the column of the other person 
      long *ptr; 
      ptr = &i; 
      *a = *ptr;
      return true;
    }
    i += 1;
  }
  return false;
}

int main()
{
  long num_of_persons = cs1010_read_long();
  char **list = malloc((size_t)num_of_persons * sizeof(char*));
  for (long i = 0; i < num_of_persons; i += 1) {
    list[i] = cs1010_read_word();
  }

  long m = cs1010_read_long();
  long n = cs1010_read_long();
  long a; 

  if (is_direct_contact(list, m, n)) {
    cs1010_println_string("direct contact");
  }
  else if (is_indirect_contact(list, m, n, &a)) {
    cs1010_print_string("contact through ");
    cs1010_println_long(a); 
  } else {
    cs1010_println_string("no contact");
  }

  for (long i = 0; i < num_of_persons; i += 1) {
    free(list[i]);
  }
  free(list);
  return 0;
}
