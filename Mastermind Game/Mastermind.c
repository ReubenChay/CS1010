/**
 * CS1010 Semester 2 AY20/21
 * Assignment 4: Mastermind
 *
 * TODO: Write documentation
 *
 * @file: mastermind.c
 * @author: Reuben Chay (Group T07)
 */
#include "cs1010.h"
#include <stdbool.h>

/** 
 * To copy an array of characters 
 *
 * @param[in,out] src The source of the array. 
 * @param[in,out] dst The destination to copy the source to. 
 */
void copy_string(char src[], char dst[]) {
  for (long i = 0; i < 4; i += 1) {
    dst[i] = src[i];
  }
}

/** 
 * Checks if there are element in the guess that are the right colour but in the wrong position. 
 *
 * @param[in] input The element being checked.
 * @param[in,out] code The actual code that was set by the coder. 
 *
 * @return Returns true if there are elements that are the right colour but in the wrong position, false otherwise.
 */
bool is_white_peg(char input, char code[]) { 
  for (long i = 0; i < 4; i += 1) {
    if (code[i] == input) {
      code[i] = 'd'; // temporarily changing the set code to prevent double counting. 
      return true;
    }
  }
  return false; 
}

/** 
 * Check the guess against the code and find the number of elements that are in the right position and colour (black pegs) 
 * and the number of elements of the right colour but in the wrong position (white pegs). 
 *
 * @pre The input arrays code and guess are both 4 elements long. 
 *
 * @param[in,out] code The input array of the code set by the coder 
 * @param[in] guess The input guess array by the guesser
 * param[out] black The number of elements in the array "guess" that are in the same position as the array "code"
 *
 * @post black <= 4.
 */
long check_guess(char code[], char guess[]) { 
  char temp[4]; // to store the original code temporarily. 
  copy_string(code, temp);
  long black = 0;

  for(long i = 0; i < 4; i += 1) { // check for guesses in the right colour and position
    if(guess[i] == code[i]) {
      black += 1;
      code[i] = 'a';
      guess [i] = 'z'; // change the code temporarily to prevent double counting, change the guess to prevent double counting. 
    }
  }

  for (long k = 1; k < 4; k += 1) {
    if (guess[0] == guess[k]) {
      guess[0] = 'x';
    }
  }
  for (long m = 2; m < 4; m += 1) {
    if (guess[1] == guess[m]) {
      guess[1] = 'y';
    }
  }
  if (guess[2] == guess[3]) { 
    guess [2] = 'q';
  }

  /**
   * Statements above are to change any remaining repeat elements in the guess, to avoid double counting in the next part
   * eg. if the current guess is "CCPP", it will be changed to "XCQP"
   * As such, the letters "c" and "p" will not be double counted later on.
   * */


  long white_count = 0;
  for (long j = 0; j < 4; j += 1) {
    if (is_white_peg(guess[j], code)) {
      white_count += 1;
    }
  }


  cs1010_print_long(black);
  cs1010_print_string(" ");
  cs1010_println_long(white_count);

  copy_string(temp, code); // restore the code to its original form. 
  return black;

}

int main()
{
  char* code = cs1010_read_word();
  if (code == NULL) {
    return 1;
  }
  char* guess; 

  long black_score = 0;
  do { 
    guess = cs1010_read_word();
    if (guess == NULL) {
      return 1;
    }
    black_score = check_guess(code, guess); 
  } while (black_score != 4); // loop to input a guess and check the guess against the set code, until the guess is correct.

  free(code);
  free(guess);

  return 0;

}
