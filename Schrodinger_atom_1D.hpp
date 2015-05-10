//
//  Schrodinger_atom_1D.hpp
//
//  Modified by Patrick Anderson on 07/05/2015.
//  "Schrodinger_atom_1D" encapsulates the interaction of an isolated atom with a strong laser
//  field. The interaction is restricted to a single active electron and spatial dimension.
//

#ifndef __SCHRODINGER_ATOM_1D_HPP_INCLUDED__
#define __SCHRODINGER_ATOM_1D_HPP_INCLUDED__

#include "grid_xkx.hpp"
#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition

class Schrodinger_atom_1D {
    
public:
    
    // Data
    grid_xkx xkx;
    double alpha;
    ArrayXd V_model;
    ArrayXcd wfn_GS;
    ArrayXcd wfn;
    double energy;
    
    // Functions
    Schrodinger_atom_1D(double alpha_);
    void set_GS(int N_it_);
    ArrayXd get_dipole(int N_it_, double dt_, ArrayXd E_);
    ArrayXd solve_TDSE_PS(int N_it_, std::complex<double> dt_, ArrayXd E_, int e_);
    
};

#endif
