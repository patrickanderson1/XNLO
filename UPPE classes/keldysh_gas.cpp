//
//  keldysh_gas.hpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "keldysh_gas" contains both linear and nonlinear parts of the medium response model.
//

#include "keldysh_gas.hpp"
#include "physics_textbook.hpp"
#include <Eigen/Dense>
#include "grid_tw.hpp"
#include "maths_textbook.hpp"
#include <mkl.h>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor
keldysh_gas::keldysh_gas(double press, physics_textbook physics_) {
    
    atom_density = press * 1.0e5 / (physics_.k_B * 300.0);  // [atoms/m^3]
    
    // Ionization rate parameters
    // Argon
    U = 15.76;  // [eV]
    C_kl = 0.95;
    n_star = 0.93;
    kappa = std::sqrt(U / 13.60);
}

//------------------------------------------------------------------------------------------------//
//  Evaluate nonlinear polarization for active frequencies
ArrayXcd keldysh_gas::nl_polarization(ArrayXd E_t_, grid_tw tw_) {
    
    // Weak, zeros
    ArrayXcd output = ArrayXcd::Zero(tw_.n_active);
    
    return(output);
}

//------------------------------------------------------------------------------------------------//
//  Calulate ionization rate (Popov, 2004)
ArrayXd keldysh_gas::ionization_rate(ArrayXd E_t_, grid_tw tw_, physics_textbook physics_,
                                     maths_textbook maths_) {
    
    ArrayXd F_t = (E_t_ / (std::pow(kappa, 3) * physics_.E_at)).abs();
    ArrayXd output = physics_.w_at * std::pow(kappa, 2) * std::sqrt(3 / maths_.pi) *
                     std::pow(C_kl, 2) * std::pow(2, 2 * n_star) * F_t.pow(1.5 - (2 * n_star)) *
                     (-2 / (3 * F_t)).exp();
    // Remove NaN
    for (int ii = 0; ii < tw_.n_t; ii++)
        if (isnan(output(ii)) == true) output(ii) = 0;
    
    return(output);
}

//------------------------------------------------------------------------------------------------//
//  Calculate free electron density (solve rate equations)
ArrayXd keldysh_gas::electron_density(ArrayXd W_t_, grid_tw tw_, maths_textbook maths_) {
    
    ArrayXd output =  atom_density * (1 - (-maths_.cumtrapz(tw_.t, W_t_)).exp());
    
    return(output);
}

//------------------------------------------------------------------------------------------------//
//  Evaluate Current density for active frequencies
ArrayXcd keldysh_gas::current_density(ArrayXd E_t_, grid_tw tw_, DFTI_DESCRIPTOR_HANDLE ft_,
                                     physics_textbook physics_, maths_textbook maths_) {
    
    // Prerequisites
    ArrayXd W_t = ionization_rate(E_t_, tw_, physics_, maths_);
    ArrayXd rho_t = electron_density(W_t, tw_, maths_);
    
    // Eliminate derivatives in governing equation by FT
    ArrayXcd B = (-std::pow(physics_.q_at, 2) * rho_t * E_t_ / physics_.m_at).
                 cast<std::complex<double> >();
    ArrayXcd C = ((rho_t * W_t * physics_.q_at * U) * E_t_ / E_t_.abs2()).
                 cast<std::complex<double> >();
    DftiComputeForward(ft_, B.data()); DftiComputeForward(ft_, C.data());
    
    // Retain active components
    ArrayXcd output = (B.segment(tw_.w_active_min_index, tw_.n_active) /
                       (std::complex<double>(0, 1) * tw_.w_active)) -
                      (physics_.eps_0 * physics_.c *
                       C.segment(tw_.w_active_min_index, tw_.n_active));
    return(output);
}


