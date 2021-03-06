#include<stdio.h>
#include<stdlib.h>
#include "atom.h"
#include "neighbor.h"
#include "force_lj.h"
#define DO_GENERATION 1
#ifndef DO_GENERATION
    //libraries to manage files
    #include <iostream>
    #include <string>
    #include <fstream>
    using namespace std;
#endif

int main(int argc, char** argv){
    //printf("\n # Running the simulation: \n");
    //variable inizialization 
    int me=0;
    int ntypes = 4;
    Atom atom(ntypes);
    Neighbor neighbor(ntypes);
    #ifdef DO_GENERATION
        #include "PythonScript/atom_data.h"
        #include "PythonScript/neigh_data.h"
    #else
        //READ ATOM FILE
        printf(" # Reading file from atom.txt :\n");
        std::fstream file ("/home/emilio/MD/miniMD/ref/atom.txt", std::ios_base::in);

        //Declare variables
        int natoms, nlocal, nghost, nmax;
        MMD_float virial, mass, temp;
        int comm_size, reverse_size, border_size, tmp;

        //Read from file
        file >> natoms;
        file >> nlocal;
        file >> nghost;
        file >> nmax;
        MMD_float* x = new MMD_float[(nlocal + nghost)*PAD];
        MMD_float* v = new MMD_float[(nlocal + nghost)*PAD];
        MMD_float* f = new MMD_float[(nlocal + nghost)*PAD];
        uint64_t aux = 0;

        int* type = new int[nlocal + nghost];

        for (int i = 0; i < (nlocal + nghost)*PAD; i++) {
            //file >> x[i];
            file >> aux;
            x[i] = *reinterpret_cast<MMD_float*> (&aux);
        }
        
        for (int i = 0; i < (nlocal + nghost)*PAD; i++) {
            //file >> v[i];
            file >> aux;
            v[i] = *reinterpret_cast<MMD_float*> (&aux);
        }
        
        for (int i = 0; i < (nlocal + nghost)*PAD; i++) {
            //file >> f[i];
            file >> aux;
            f[i] = *reinterpret_cast<MMD_float*> (&aux);
        }
        
        for (int i = 0; i < nlocal + nghost; i++) {
            file >> type[i];
        }
        
        file >> virial;
        file >> mass;
        file >> comm_size;
        file >> reverse_size;
        file >> border_size;
        file.close();

        //READ NEIGHBOR FILE
        printf(" # Reading file from neighbors.txt :\n");
        std::fstream neigh ("/home/emilio/MD/miniMD/ref/neighbors.txt", std::ios_base::in);

        //Declare variables
        int f_nmax, f_maxneighs;

        //Read from file
        neigh >> f_maxneighs;
        neigh >> f_nmax;
        int* f_numneigh = new int[f_nmax];
        int* f_neighbors = new int[f_nmax*f_maxneighs];
        
        for (int i = 0; i < f_nmax; i++) {
            neigh >> f_numneigh[i];
        }
        
        for (int i = 0; i < f_nmax * f_maxneighs; i++) {
            neigh >> f_neighbors[i];
        }
        neigh.close();

    #endif
    //Assign the variables for ATOMS
    atom.natoms = natoms;
    atom.nlocal = nlocal;
    atom.nghost = nghost;
    atom.nmax = nmax;
    #ifdef DO_GENERATION
        for (int i = 0; i < (nlocal + nghost)*PAD; i++) {
            x_f[i] = *reinterpret_cast<MMD_float*> (&x[i]);
            //PER C x_f[i] = *((MMD_float*)(&x[i]));
        }
        for (int i = 0; i < (nlocal + nghost)*PAD; i++) {
            v_f[i] = *reinterpret_cast<MMD_float*> (&v[i]);
        }
        for (int i = 0; i < (nlocal + nghost)*PAD; i++) {
            f_f[i] = *reinterpret_cast<MMD_float*> (&f[i]);
        }
        atom.x = x_f;
        atom.v = v_f;
        atom.f = f_f;
    #else
        atom.x = x;
        atom.v = v;
        atom.f = f;
    #endif
    atom.ntypes = ntypes;
    atom.type = type;
    atom.virial = virial;
    atom.mass = mass;
    atom.comm_size = comm_size;
    atom.border_size = border_size;
    atom.reverse_size = reverse_size;
    /*
    printf("\t> Natoms: %d\n", atom.natoms);
    printf("\t> Nlocal: %d\n", atom.nlocal);
    printf("\t> Nghost: %d\n", atom.nghost);
    printf("\t> x[0]: %f\n", atom.x[0]);
    printf("\t> v[0]: %f\n", atom.v[0]);
    printf("\t> f[0]: %f\n", atom.f[0]);
    printf("\t> type[0]: %d\n", atom.type[0]);
    printf(" # Done ...\n");
    */

    //Assign the variables for NEIGHBORS
    neighbor.set_nmax(f_nmax);
    neighbor.maxneighs = f_maxneighs;
    neighbor.numneigh = f_numneigh;
    neighbor.neighbors = f_neighbors;
    /*
    printf("\t> Nmax: %d\n", f_nmax);
    printf("\t> Maxneighs: %d\n", neighbor.maxneighs);
    printf(" # Done ...\n");
    */

    //declare and set parameters of the force
    //printf(" # Setting up force :\n");
    Force* force = (Force*) new ForceLJ(ntypes);
    MMD_float epsilon, sigma;
    epsilon=1.0;
    sigma=1.0;
    force->cutforce=2.5;
    for(int i=0; i<ntypes*ntypes; i++) {
      force->epsilon[i] = epsilon;
      force->sigma[i] = sigma;
      force->sigma6[i] = sigma*sigma*sigma*sigma*sigma*sigma;
    }
    force->setup();
    /*
    printf("\t> epsilon: %f\n", epsilon);
    printf("\t> sigma: %f\n", sigma);
    printf("\t> cutforce: %f\n", force->cutforce);
    */

    //Run the simulation
    force->compute_original(atom, neighbor, me);
}
