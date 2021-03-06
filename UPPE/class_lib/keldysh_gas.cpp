//
//  keldysh_gas.hpp
//
//  Modified by Patrick Anderson on 03/09/2015.
//  "keldysh_gas" contains the medium response model.
//

#include "keldysh_gas.hpp"
#include "physics_textbook.hpp"
#include "grid_tw.hpp"
#include <mkl.h>
#include <Eigen/Dense>
#include "maths_textbook.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor
keldysh_gas::keldysh_gas(double press_, grid_tw tw_, DFTI_DESCRIPTOR_HANDLE ft_) {
    
    tw = tw_;
    ft = ft_;
    atom_density = press_ * 1.0e5 / (physics.k_B * 300.0);  // [atoms/m^3]
    
    // Ionization parameters, argon
    U = 15.76;  // [eV]
    C_kl = 0.95;
    n_star = 0.93;
    kappa = std::sqrt(U / 13.60);
}

//------------------------------------------------------------------------------------------------//
//  Evaluate nonlinear polarization for active frequencies
ArrayXcd keldysh_gas::nl_polarization(ArrayXd E_t_) {
    
    // Weak, zeros
    ArrayXcd output = ArrayXcd::Zero(tw.n_active);
    
    return(output);
}

//------------------------------------------------------------------------------------------------//
//  Calulate ionization rate (Popov, 2004)
ArrayXd keldysh_gas::ionization_rate(ArrayXd E_t_) {
    
    ArrayXd F_t = (E_t_ / (std::pow(kappa, 3.0) * physics.E_at)).abs();
    ArrayXd output = physics.w_at * std::pow(kappa, 2.0) * std::sqrt(3.0 / maths.pi) *
                     std::pow(C_kl, 2.0) * std::pow(2.0, 2.0 * n_star) * F_t.pow(1.5 - (2.0 * n_star)) *
                     (-2.0 / (3.0 * F_t)).exp();
    for (int ii = 0; ii < tw.n_t; ii++)     // Remove NaN
        if (isnan(output(ii)) == true) output(ii) = 0;

    return(output);
}

//------------------------------------------------------------------------------------------------//
//  Calculate free electron density (solve rate equations)
ArrayXd keldysh_gas::electron_density(ArrayXd W_t_) {
    
    ArrayXd output =  atom_density * (1.0 - (-maths.cumtrapz(tw.t, W_t_)).exp());

    return(output);
}

//------------------------------------------------------------------------------------------------//
//  Evaluate Current density for active frequencies
ArrayXcd keldysh_gas::current_density(ArrayXd E_t_) {
    
    // Prerequisites
    ArrayXd W_t = ionization_rate(E_t_);
    ArrayXd rho_t = electron_density(W_t);
    
    // Eliminate derivatives in governing equation by FT
    ArrayXcd B = (-std::pow(physics.q_at, 2.0) * rho_t * E_t_ / physics.m_at).
                 cast<std::complex<double> >();
    ArrayXd temp_1 = rho_t * W_t * physics.q_at * U * E_t_ / E_t_.abs2();
    for (int ii = 0; ii < tw.n_t; ii++)     // Remove NaN
        if (isnan(temp_1(ii)) == true) temp_1(ii) = 0;
    ArrayXcd C = temp_1.cast<std::complex<double> >();
    DftiComputeForward(ft, B.data()); DftiComputeForward(ft, C.data());
    
    // Retain active components
    ArrayXcd output = (B.segment(tw.w_active_min_index, tw.n_active) /
                       (std::complex<double>(0.0, -1.0) * tw.w_active)) -
                      (physics.eps_0 * physics.c *
                       C.segment(tw.w_active_min_index, tw.n_active));
    return(output);
}


