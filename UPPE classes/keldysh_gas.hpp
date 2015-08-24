//
//  keldysh_gas.hpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "keldysh_gas" contains both linear and nonlinear parts of the medium response model.
//

#ifndef __KELDYSH_GAS_HPP_INCLUDED__
#define __KELDYSH_GAS_HPP_INCLUDED__

#include "physics_textbook.hpp"
#include <Eigen/Dense>
#include "grid_tw.hpp"
#include "maths_textbook.hpp"
#include <mkl.h>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class keldysh_gas {
    
public:
    // Data
    double atom_density;
    double U;
    double C_kl;
    double n_star;
    double kappa;
    
    // Functions
    keldysh_gas(double press_, physics_textbook physics_);
    ArrayXcd nl_polarization(ArrayXd E_t_, grid_tw tw_);
    ArrayXd ionization_rate(ArrayXd E_t_, grid_tw tw_, physics_textbook physics_,
                            maths_textbook maths_);
    ArrayXd electron_density(ArrayXd W_t_, grid_tw tw_, maths_textbook maths_);
    ArrayXcd current_density(ArrayXd E_t_, grid_tw tw_, DFTI_DESCRIPTOR_HANDLE ft_,
                             physics_textbook physics_, maths_textbook maths_);
};

#endif
