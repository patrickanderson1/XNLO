//
//  laser_pulse.cpp
//
//  Modified by Patrick Anderson on 07/05/2015.
//  "laser_pulse" contains a time varying electric field. The intital conditions are passed to the
//  constructor and field can be updated as it propagates.
//

#ifndef __LASER_PULSE_HPP_INCLUDED__
#define __LASER_PULSE_HPP_INCLUDED__

#include <Eigen/Dense>
#include "grid_xkx.hpp"
#include "grid_tw.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition

class laser_pulse {
    
public:
    
    // Data
    ArrayXXd E;
    
    // Functions
    laser_pulse(double P_av_, double RR_, double FWHM_, double l_0_, double CEO_,
                double spot_radius_, double ROC_, grid_xkx xkx_, grid_tw tw_);

};

#endif
