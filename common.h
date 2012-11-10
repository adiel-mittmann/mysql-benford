#ifndef BENFORD_COMMON_H
#define BENFORD_COMMON_H

#include <mysql.h>
#include <math.h>

// Holds the expected frequency for digits 1-9.
const double benford_dist[9];

// Structure used by functions to compute their results.
typedef struct{
  long digits[9];
  long count;
  double freq[9];
} benford_data;

// Function to be called when all rows of a group have been
// processed. Calculates the frequency of digits, filling the "freq" field.
void finish(benford_data *data);

// Calculates the maximum difference between expected and observed frequency.
double max_diff(benford_data *data);

// "This function is called when MySQL finds the first row in a new group."
my_bool common_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

// "The deinitialization function".
void common_deinit(UDF_INIT *initid);

// "This function is called when MySQL needs to reset the summary results."
void common_clear(UDF_INIT *initid, char *is_null, char *error);

// "This function is called for all rows that belong to the same group."
void common_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

#endif
