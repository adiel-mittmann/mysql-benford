#include "common.h"

my_bool benf_max_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  return common_init(initid, args, message);
}

void benf_max_deinit(UDF_INIT *initid)
{
  common_deinit(initid);
}

void benf_max_clear(UDF_INIT *initid, char *is_null, char *error)
{
  common_clear(initid, is_null, error);
}

void benf_max_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
  common_add(initid, args, is_null, error);
}

double benf_max(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
  benford_data *data = (benford_data *)initid->ptr;
  finish(data);
  return max_diff(data);
}
