//
//  laser_pulse.cpp
//
//  Modified by Patrick Anderson on 07/05/2015.
//  "laser_pulse" contains a time varying electric field. The intital conditions are passed to the
//  constructor and field can be updated as it propagates.
//

#include "laser_pulse.hpp"
#include "grid_xkx.hpp"
#include "grid_tw.hpp"
#include "physics_textbook.hpp"
#include "maths_textbook.hpp"
#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor

laser_pulse::laser_pulse(double P_av_, double RR_, double FWHM_, double l_0_, double CEO_,
                         double spot_radius_, double ROC_, grid_xkx xkx_, grid_tw tw_) {

    maths_textbook maths;
    physics_textbook physics;
    
    // Time
    double P_peak = 0.94 * ((P_av_ / RR_) / FWHM_);
    double E_peak = std::sqrt((4 * P_peak) /
                              (physics.c * physics.eps_0 * maths.pi * (std::pow(spot_radius_, 2))));
    ArrayXd envelope_t = (-2.77 * (tw_.t / FWHM_).pow(2)).exp();
    
    // Space
    ArrayXd envelope_x = (-(xkx_.x / spot_radius_).pow(2)).exp();
    
    // Space-time
    E = ArrayXXd::Zero(tw_.N_t, xkx_.N_x);
    double f_0 = physics.c / l_0_;
    double w_0 = 2 * maths.pi * f_0;
    ArrayXd phi = (maths.pi * xkx_.x.pow(2) / (l_0_ * ROC_)) + CEO_;
    
    for (int ii = 0; ii < xkx_.N_x; ii++) {
        E.col(ii) = E_peak * envelope_x(ii) * envelope_t * ((w_0 * tw_.t) + phi(ii)).cos();
    }
    
}

