//
//  capillary_fibre.hpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "capillary_fibre" describes the dimensions and dispersion properties of a dielectric capillary
//  type fibre.
//

#ifndef __CAPILLARY_FIBRE_HPP_INCLUDED__
#define __CAPILLARY_FIBRE_HPP_INCLUDED__

#include <Eigen/Dense>
#include "grid_tw.hpp"
#include "grid_rkr.hpp"
#include "physics_textbook.hpp"
#include "maths_textbook.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class capillary_fibre {
    
public:
    // Data
    ArrayXXd beta;
    ArrayXXd alpha;
    double Z;
    double R;
    double n_glass;
    
    // Functions
    capillary_fibre(double Z_, grid_rkr rkr_, grid_tw tw_, physics_textbook physics_,
                    maths_textbook maths_);
};

#endif
