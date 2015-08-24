//
//  grid_tw.hpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "grid_tw" is a linear temporal grid. The spectral counterpart of this grid is evaluated and
//  made accessible.
//

#ifndef __GRID_TW_HPP_INCLUDED__
#define __GRID_TW_HPP_INCLUDED__

#include <Eigen/Dense>
#include "maths_textbook.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class grid_tw {
    
public:
    // Data
    ArrayXd t;
    ArrayXd w_active;
    int n_t;
    int n_active;
    int w_active_min_index;
    
    // Functions
    grid_tw(int N_t_, double T_, double w_active_min_, double w_active_max_, maths_textbook maths_);
};

#endif
