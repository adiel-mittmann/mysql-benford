#include "common.h"

my_bool benf_mstar_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  return common_init(initid, args, message);
}

void benf_mstar_deinit(UDF_INIT *initid)
{
  common_deinit(initid);
}

void benf_mstar_clear(UDF_INIT *initid, char *reject_null, char *error)
{
  common_clear(initid, reject_null, error);
}

void benf_mstar_add(UDF_INIT *initid, UDF_ARGS *args, char *reject_null, char *error)
{
  common_add(initid, args, reject_null, error);
}

long long benf_mstar(UDF_INIT *initid, UDF_ARGS *args, char *reject_null, char *error)
{
  benford_data *data = (benford_data *)initid->ptr;
  finish(data);

  double m_star = sqrt((double)data->count) * max_diff(data);

  if (m_star > 1.212)
    return 1;
  else
    return 0;
}
