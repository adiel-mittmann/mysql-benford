#include "common.h"

my_bool BENF_MSTAR_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  return common_init(initid, args, message);
}

void BENF_MSTAR_deinit(UDF_INIT *initid)
{
  common_deinit(initid);
}

void BENF_MSTAR_clear(UDF_INIT *initid, char *reject_null, char *error)
{
  common_clear(initid, reject_null, error);
}

void BENF_MSTAR_add(UDF_INIT *initid, UDF_ARGS *args, char *reject_null, char *error)
{
  common_add(initid, args, reject_null, error);
}

long long BENF_MSTAR(UDF_INIT *initid, UDF_ARGS *args, char *reject_null, char *error)
{
  benford_data *data = (benford_data *)initid->ptr;
  finish(data);

  double m_star = sqrt((double)data->count) * max_diff(data);

  if (m_star > 1.212)
    return 1;
  else
    return 0;
}
