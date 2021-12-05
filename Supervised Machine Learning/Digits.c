/**
 * CS1010 Semester 2 AY20/21
 * Assignment 9: Digits
 *
 * This program reads in handwritten digits in the form of training samples
 * and testing samples. Based on the training samples as references, 
 * it tells what the handwritten digits in the testing samples are. 
 *
 * @file: digits.c
 * @author: Reuben Chay (Group T07)
 */

#include "cs1010.h"

#define NCOLS 28
#define NROWS 28
#define WHITE '.'
#define BLACK '#'
#define K 5

typedef struct {
  char numbergrid[NROWS][NCOLS];
  long num;
} digit;

typedef struct {
  long neighbour_digit;
  long dist; 
} neighbour;


typedef struct {
  long count;
  long dist;
} top5_counter;


/**
 * Finds the distance between two given samples of a 28x28 array while updating 
 * the maximum distance between a pair of samples  so far and its corresponding index
 *
 * @param[in] numbergrid One of the two samples we are comparing (training sample)
 * @param[in] numbergrid2 The other of the two samples we are comparing (testing sample)
 * @param[in, out] max_dist The maximum distance so far out of all the pairs of samples
 * @param[in] counter The counter-th training sample that we are comparing our testing sample against
 * @param[in, out] max_index The index of the training sample that has the maximum distance so far
 *
 * @pre Both numbergrid and numbergrid2 are not NULL. 
 *
 * @return Returns the distance between the two samples (training vs testing samples)
 *
 */
long distance(char numbergrid[][NCOLS], char numbergrid2[][NCOLS], long *max_dist, long counter, long *max_index) {
  long count = 0;
  for (long i = 0; i < 28; i += 1) {
    for (long k = 0; k < 28; k += 1) {
      if (numbergrid[i][k] != numbergrid2[i][k]) {
        count += 1;
        if (count > *max_dist) {
          if (counter < 5) {
            *max_dist = count;
            *max_index = counter;
          }
          if (counter >= 5) {
            return -1; // returns -1 if the count exceeds the maximum distance so we can stop counting 
          }
        }
      }
    }
  }
  return count;
}


/**
 * Finds the maximum distance and its corresponding index amongst the top 5 neighbour samples thus far.
 *
 * @param[in] distances The array of the top 5 neighbours we are scanning through
 * @param[in, out] max_dist Maximum distance so far 
 * @param[in, out] max_index The corresponding index of the sample with the maximum distance 
 *
 * @pre distances is not NULL 
 *
 */
void find_max(neighbour *distances, long *max_dist, long *max_index) {
  for (long i = 0; i < 5; i += 1) {
    if (distances[i].dist > *max_dist) {
      *max_dist = distances[i].dist;
      *max_index = i;
    }
  }
}


/**
 * Compares a single test case against all the training cases, obtaining the top 5 neighbour samples 
 * and inputting them into an array of 5 elements. 
 *
 * @param[in, out] distances The array containing the top 5 neighbour samples
 * @param[in] training The array containing all the training samples - its representation on a 28x28 array and its corresponding digit
 * @param[in] testing The testing sample - containing its digit and its representation ona a 28x28 array 
 * @param[in] n The number of training sampls in the 'training' array 
 *
 */
void get_top5(neighbour *distances, digit *training, digit testing, long n) {
  long max_dist = 0;
  long max_index = 0;
  for (long i = 0; i < 5; i += 1) {
    distances[i].dist = distance(training[i].numbergrid, testing.numbergrid, &max_dist, i, &max_index);
    distances[i].neighbour_digit = training[i].num;
  }

  for (long i = 5; i < n; i += 1) {
    long dist_value = distance(training[i].numbergrid, testing.numbergrid, &max_dist, i, &max_index);
    if ((dist_value < max_dist) && (dist_value != -1)) {
      distances[max_index].dist = dist_value;
      distances[max_index].neighbour_digit = training[i].num;

      find_max(distances, &max_dist, &max_index);
      // after updating the new maximums, scan through the array again to ensure that max_index and max_dist is still correct
    }

    if (dist_value == max_dist && dist_value != -1) {
      if (training[i].num < distances[max_index].neighbour_digit) {
        distances[max_index].neighbour_digit = training[i].num;
        // no need to find max again since max_dist remains the same
      }
    }
  }
}

/**
 * From the array of the top 5 neighbour samples, finds the highest occuring digit to return the recognised value 
 *
 * @param[in] distances The array containing the top 5 neighbour samples
 *
 * @pre distances is not NULL 
 *
 * @return Returns the recognised value. 
 */
long recognised_value(neighbour *distances) {
  top5_counter list[10];
  for (long i = 0; i < 10; i += 1) {
    list[i].count = 0;
    list[i].dist = 785;
  }


  for (long i = 0; i < 5; i += 1) {
    long num = distances[i].neighbour_digit; 

    if (list[num].count > 0) {
      if (distances[i].dist < list[num].dist) {
        list[num].dist = distances[i].dist;
      }
    } else if (list[num].count == 0) {
      list[num].dist = distances[i].dist;
    }

    list[num].count += 1;
  }


  long max_count = 0; 
  long max_digit = 0;
  for (long i = 0; i < 10; i += 1) {
    if (list[i].count > max_count) {
      max_count = list[i].count; 
      max_digit = i;
    }
    if (list[i].count == max_count) {
      if (list[i].dist < list[max_digit].dist) {
        max_digit = i; 
      } 
    }
    /** since we are comparing from 0 to 9 in order, there is no need to compare the case where their counts and 
     * their distances are the same, since we will return the smaller digit. When checking in increasing order, if we encounter 
     * such a situation, the smaller digit is already in place as the max_digit
     */
  }

  return max_digit; 
}


int main() {
  long n = cs1010_read_long(); // number of training samples 
  digit *training = malloc((size_t)n * sizeof(digit));
  for (long i = 0; i < n ; i += 1) {
    training[i].num = cs1010_read_long();
    for (long k = 0; k < NROWS; k += 1) {
      for (long j = 0; j < NCOLS; j += 1) {
        training[i].numbergrid[k][j] = (char)getchar(); 
      }
      getchar();
    }
  }

  long count = 0;

  long m = cs1010_read_long(); // number of testing samples 
  for (long i = 0; i < m; i += 1) {
    digit testing; 
    testing.num = cs1010_read_long();
    for (long k = 0; k < NROWS; k += 1) {
      for (long j = 0; j < NCOLS; j += 1) { 
        testing.numbergrid[k][j] = (char)getchar();
      }
      getchar();
    }

    neighbour distances[5]; // array to store the top 5 neighbour samples 

    get_top5(distances, training, testing, n);

    long recognised = recognised_value(distances);
    cs1010_print_long(testing.num);
    cs1010_print_string(" ");
    cs1010_println_long(recognised);

    if (recognised == testing.num) {
      count += 1;
    }
  }

  double accuracy = ((double)count / m) * 100.0;
  cs1010_println_double(accuracy);

  return 0;
}

