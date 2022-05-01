#ifndef NEIGHBOR_H
#define NEIGHBOR_H

#include "atom.h"
#include "threadData.h"
//#include "timer.h"

class Neighbor
{
  public:
    int every;                       // re-neighbor every this often
    int nbinx, nbiny, nbinz;         // # of global bins
    MMD_float cutneigh;                 // neighbor cutoff
    MMD_float* cutneighsq;               // neighbor cutoff squared
    int ncalls;                      // # of times build has been called
    int max_totalneigh;              // largest # of neighbors ever stored

    int* numneigh;                   // # of neighbors for each atom
    int* neighbors;                  // array of neighbors of each atom
    int maxneighs;				   // max number of neighbors per atom
    int halfneigh;

    MMD_int ghost_newton;
    int count;
    Neighbor(int ntypes_);
    ~Neighbor();
    int setup(Atom &);               // setup bins based on box and cutoff
    void build(Atom &);              // create neighbor list
    void set_nmax(int f_nmax);
    //Timer* timer;

    ThreadData* threads;

    // Atom is going to call binatoms etc for sorting
    void binatoms(Atom & atom, int count = -1);           // bin all atoms

    int* bincount;                    // ptr to 1st atom in each bin
    int* bins;                       // ptr to next atom in each bin
    int mbins;                       // binning parameters
    int atoms_per_bin;
  private:
    MMD_float xprd, yprd, zprd;      // box size

    int nmax;                        // max size of atom arrays in neighbor
    int ntypes;                      // number of atom types

    int nstencil;                    // # of bins in stencil
    int* stencil;                    // stencil list of bin offsets
    int mbinx, mbiny, mbinz;
    int mbinxlo, mbinylo, mbinzlo;
    MMD_float binsizex, binsizey, binsizez;
    MMD_float bininvx, bininvy, bininvz;

    int resize;

    MMD_float bindist(int, int, int);   // distance between binx
    int coord2bin(MMD_float, MMD_float, MMD_float);   // mapping atom coord to a bin
};

#endif
