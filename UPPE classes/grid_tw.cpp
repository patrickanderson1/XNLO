//
//  grid_tw.cpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "grid_tw" is a linear temporal grid. The spectral counterpart of this grid is evaluated and
//  made accessible.
//

#include "grid_tw.hpp"
#include "maths_textbook.hpp"
#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor
grid_tw::grid_tw(int n_t_, double T_, double w_active_min_, double w_active_max_,
                 maths_textbook maths_) {
        
    // Temporal
    n_t = n_t_;
    t = ArrayXd::LinSpaced(n_t, -T_ / 2.0, T_ / 2.0);
    double dt = t(1) - t(0);
    
    // Spectral
    ArrayXd w = 2.0 * maths_.pi * ArrayXd::LinSpaced(n_t, 0.0, n_t - 1.0) * (1.0 / (dt * n_t));
    w_active_min_index = 0;
    while (w(w_active_min_index) < w_active_min_)
        w_active_min_index++;
    int temp = 0;
    while (w(temp) < w_active_max_)
        temp++;
    n_active = temp - w_active_min_index;
    w_active = w.segment(w_active_min_index, n_active);
}

