//
//  laser_pulse.hpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "laser_pulse" contains the active spectral amplitudes at the current z-position.
//

#include "laser_pulse.hpp"
#include "grid_tw.hpp"
#include "grid_rkr.hpp"
#include <mkl.h>
#include "DHT.hpp"
#include "physics_textbook.hpp"
#include "maths_textbook.hpp"
#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor
laser_pulse::laser_pulse(double p_av_, double rep_, double fwhm_, double l_0_, double ceo_,
                         double waist_, grid_tw tw_, grid_rkr rkr_, DFTI_DESCRIPTOR_HANDLE ft_,
                         DHT ht_, physics_textbook physics_, maths_textbook maths_) {
    
    // Temporal
    double p_pk = 0.94 * ((p_av_ / rep_) / fwhm_);
    double E_pk = std::sqrt((4.0 * p_pk) / (physics_.c * physics_.eps_0 * maths_.pi *
                                          (std::pow(waist_, 2.0))));
    ArrayXd env_t = (-2.77 * (tw_.t / fwhm_).pow(2.0)).exp();
    ArrayXd carr_t = ((2.0 * maths_.pi * physics_.c / l_0_) * tw_.t).cos();
    
    // Spatial
    ArrayXd env_r = (-(rkr_.r / waist_).pow(2.0)).exp();
    
    // Spatio-temporal
    E_t_r = (E_pk * env_t * carr_t).matrix() * env_r.matrix().transpose();
    
    // Apply forward spectral transform
    ArrayXXcd temp_1 = E_t_r.cast<std::complex<double> >();
    for (int ii = 0; ii < rkr_.n_r; ii++)
        DftiComputeForward(ft_, temp_1.col(ii).data());
    
    ArrayXXcd temp_2 = temp_1.block(tw_.w_active_min_index, 0, tw_.n_active, rkr_.n_r);
    for (int ii = 0; ii < tw_.n_active; ii++)
        temp_2.row(ii) = ht_.forward(temp_2.row(ii));
    A_w_active = temp_2.block(0, 0, tw_.n_active, rkr_.n_m);
 }

