#include "stdio.h"
#include "stdlib.h"

#include "neighbor.h"
#include "openmp.h"

#define FACTOR 0.999
#define SMALL 1.0e-6

Neighbor::Neighbor(int ntypes_)
{
  ncalls = 0;
  ntypes = ntypes_;
  max_totalneigh = 0;
  numneigh = NULL;
  neighbors = NULL;
  maxneighs = 100;
  nmax = 0;
  bincount = NULL;
  bins = NULL;
  atoms_per_bin = 8;
  stencil = NULL;
  threads = NULL;
  halfneigh = 0;
  ghost_newton = 1;
  cutneighsq = new MMD_float[ntypes*ntypes];
}

Neighbor::~Neighbor()
{
#ifdef ALIGNMALLOC
  if(numneigh) _mm_free(numneigh);
  if(neighbors) _mm_free(neighbors);
#else 
  if(numneigh) free(numneigh);
  if(neighbors) free(neighbors);
#endif
  
  if(bincount) free(bincount);

  if(bins) free(bins);
}

void Neighbor::set_nmax(int f_nmax) {
  nmax = f_nmax;
}

