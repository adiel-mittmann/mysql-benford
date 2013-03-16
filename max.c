#include "common.h"

my_bool BENF_MAX_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  return common_init(initid, args, message);
}

void BENF_MAX_deinit(UDF_INIT *initid)
{
  common_deinit(initid);
}

void BENF_MAX_clear(UDF_INIT *initid, char *is_null, char *error)
{
  common_clear(initid, is_null, error);
}

void BENF_MAX_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
  common_add(initid, args, is_null, error);
}

double BENF_MAX(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
  benford_data *data = (benford_data *)initid->ptr;
  finish(data);
  return max_diff(data);
}
