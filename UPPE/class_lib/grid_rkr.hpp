//
//  grid_rkr.hpp
//
//  Modified by Patrick Anderson on 03/09/2015.
//  "grid_rkr" is a non-uniform radial grid. The spectral counterpart of this grid is evaluated and
//  accessible.
//

#ifndef __GRID_RKR_HPP_INCLUDED__
#define __GRID_RKR_HPP_INCLUDED__

#include <Eigen/Dense>
#include "maths_textbook.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class grid_rkr {
    
public:
    // Data
    ArrayXd r;
    ArrayXd kr;
    int n_r;
    double R;
    int n_m;
    
    // Functions
    grid_rkr();
    grid_rkr(int n_r_, double R_, int n_m_, maths_textbook maths_);
};

#endif
