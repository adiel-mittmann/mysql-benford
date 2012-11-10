#include "common.h"

#include <string.h>
#include <stdlib.h>

#include <stdio.h>

const double benford_dist[] = {
  0.30102999566398,
  0.17609125905568,
  0.12493873660830,
  0.09691001300806,
  0.07918124604762,
  0.06694678963061,
  0.05799194697769,
  0.05115252244738,
  0.04575749056068
};

my_bool common_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1)
  {
    strcpy(message, "This function requires exactly one argument");
    return 1;
  }

  args->arg_type[0] = REAL_RESULT;

  initid->ptr = malloc(sizeof(benford_data));
  initid->decimals = 31;

  return 0;
}

void common_deinit(UDF_INIT *initid)
{
  free(initid->ptr);
}

void common_clear(UDF_INIT *initid, char *is_null, char *error)
{
  benford_data *data = (benford_data *)initid->ptr;
  int i;
  for (i = 1; i <= 9; i++)
  {
    data->digits[i - 1] = 0;
    data->freq[i - 1] = 0.0;
  }
  data->count = 0;
}

void common_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
  if (args->args[0] == 0)
    return;

  double value = *((double *)args->args[0]);
  value = value / pow(10, (int)log10(value));
  if (value < 1)
    value *= 10;

  int fd = (int)value;
  if (fd < 1 || fd > 9)
    return;

  benford_data *data = (benford_data *)initid->ptr;
  data->digits[fd - 1] += 1;
  data->count += 1;
}

void finish(benford_data *data)
{
  fprintf(stderr, "FINISH\n");
  for (int i = 1; i <= 9; i++)
  {
    data->freq[i - 1] = data->digits[i - 1] * 1.0 / data->count;
    fprintf(stderr, "(%d, %.8f)\n", i, data->freq[i - 1]);
  }
}

double max_diff(benford_data *data)
{
  double result = 0.0;

  for (int i = 1; i <= 9; i++)
  {
    double diff = fabs(data->freq[i - 1] - benford_dist[i - 1]);
    if (diff > result)
      result = diff;
  }

  return result;

}
