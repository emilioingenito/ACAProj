#ifndef LJS_H_
#define LJS_H_

#include "types.h"

struct In {
  int nx, ny, nz;
  MMD_float t_request;
  MMD_float rho;
  int units;
  ForceStyle forcetype;
  MMD_float epsilon, sigma;
  char* datafile;
  int ntimes;
  MMD_float dt;
  int neigh_every;
  MMD_float force_cut;
  MMD_float neigh_cut;
  int thermo_nstat;
};

#endif
