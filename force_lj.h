#ifndef FORCELJ_H
#define FORCELJ_H

#include "atom.h"
#include "neighbor.h"
#include "threadData.h"
#include "types.h"
#include "force.h"
#include "comm.h"

class ForceLJ : Force
{
  public:

    ForceLJ(int ntypes_);
    virtual ~ForceLJ();
    void setup();

  public:
    //template<int EVFLAG>
    void compute_original(Atom &, Neighbor &, int);
};

#endif
