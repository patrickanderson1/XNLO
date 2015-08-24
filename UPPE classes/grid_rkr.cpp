//
//  grid_rkr.cpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "grid_rkr" is a non-uniform radial grid. The spectral counterpart of this grid is evaluated and
//  accessible.
//

#include "grid_rkr.hpp"
#include "maths_textbook.hpp"
#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor
grid_rkr::grid_rkr(int n_r_, double R_, int n_m_, maths_textbook maths_) {
    
    n_r = n_r_;
    R = R_;
    n_m = n_m_;
    
    r = R * maths_.J0_zeros.head(n_r) / maths_.J0_zeros(n_r);
    kr = maths_.J0_zeros.head(n_r) / R;
}