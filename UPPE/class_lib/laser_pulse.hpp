//
//  laser_pulse.hpp
//
//  Modified by Patrick Anderson on 03/09/2015.
//  "laser_pulse" contains the active spectral amplitudes and governs their propagation over
//  longitudinal step dz.
//

#ifndef __LASER_PULSE_HPP_INCLUDED__
#define __LASER_PULSE_HPP_INCLUDED__

#include "physics_textbook.hpp"
#include "maths_textbook.hpp"
#include "grid_tw.hpp"
#include "grid_rkr.hpp"
#include <mkl.h>
#include "DHT.hpp"
#include <Eigen/Dense>
#include "capillary_fibre.hpp"
#include "keldysh_gas.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class laser_pulse {
    // Data
    physics_textbook physics;
    maths_textbook maths;
    grid_tw tw;
    grid_rkr rkr;
    DFTI_DESCRIPTOR_HANDLE ft;
    DHT ht;
    ArrayXXcd Y_4;
    ArrayXXcd Y_5;
    double e;
    
    // Functions
    void RK_F_45(double dz_, capillary_fibre capillary_, keldysh_gas gas_);
    ArrayXXcd RHS_UPPE(double dz_, ArrayXXcd A_w_active, capillary_fibre capillary_,
                       keldysh_gas gas_);
    
public:
    // Data
    ArrayXXcd A_w_active;
    
    // Functions
    laser_pulse(double p_av_, double rep_, double fwhm_, double l_0_, double ceo_, double waist_,
                grid_tw tw_, grid_rkr rkr_, DFTI_DESCRIPTOR_HANDLE ft_, DHT ht_);
    void propagate(double dz_, capillary_fibre capillary_, keldysh_gas gas_);
};

#endif
