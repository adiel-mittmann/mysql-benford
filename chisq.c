#include "common.h"

my_bool BENF_CHISQ_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  return common_init(initid, args, message);
}

void BENF_CHISQ_deinit(UDF_INIT *initid)
{
  common_deinit(initid);
}

void BENF_CHISQ_clear(UDF_INIT *initid, char *chisq_null, char *error)
{
  common_clear(initid, chisq_null, error);
}

void BENF_CHISQ_add(UDF_INIT *initid, UDF_ARGS *args, char *chisq_null, char *error)
{
  common_add(initid, args, chisq_null, error);
}

long long BENF_CHISQ(UDF_INIT *initid, UDF_ARGS *args, char *chisq_null, char *error)
{
  benford_data *data = (benford_data *)initid->ptr;
  finish(data);

  double expected[9];
  for (int i = 1; i <= 9; i++)
    expected[i - 1] = data->count * benford_dist[i - 1];

  double chisq = 0.0;
  for (int i = 1; i <= 9; i++)
  {
    double diff = data->digits[i - 1] - expected[i - 1];
    chisq += diff * diff / expected[i - 1];
  }

  
  if (chisq >= 26.125)
    return 1;
  else
    return 0;
}
