#ifndef FORCE_H_
#define FORCE_H_

#include "ljs.h"
#include "atom.h"
#include "neighbor.h"
#include "comm.h"

class Force
{
  public:
    MMD_float cutforce;
    MMD_float* cutforcesq;
    MMD_float eng_vdwl;
    MMD_float mass;
    MMD_int evflag;
    MMD_float virial;
    int ntypes;

    Force() {};
    virtual ~Force() {};
    virtual void setup() {};
    virtual void finalise() {};
    virtual void compute_original(Atom &, Neighbor &, int){};

    int use_sse;
    int use_oldcompute;
    ThreadData* threads;
    MMD_int reneigh;
    Timer* timer;

    MMD_float *epsilon, *sigma6, *sigma; //Parameters for LJ only

    ForceStyle style;
  protected:

    MMD_int me;
};

#endif
