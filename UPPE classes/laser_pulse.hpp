//
//  laser_pulse.hpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "laser_pulse" contains the active spectral amplitudes at the current z-position.
//

#ifndef __LASER_PULSE_HPP_INCLUDED__
#define __LASER_PULSE_HPP_INCLUDED__

#include <Eigen/Dense>
#include "grid_tw.hpp"
#include "grid_rkr.hpp"
#include <mkl.h>
#include "DHT.hpp"
#include "physics_textbook.hpp"
#include "maths_textbook.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class laser_pulse {
    
public:
    // Data
    ArrayXXd E_t_r;
    ArrayXXcd A_w_active;
    
    // Functions
    laser_pulse(double p_av_, double rep_, double fwhm_, double l_0_, double ceo_, double waist_,
                grid_tw tw_, grid_rkr rkr_, DFTI_DESCRIPTOR_HANDLE ft_, DHT ht_,
                physics_textbook physics_, maths_textbook maths_);
};

#endif
