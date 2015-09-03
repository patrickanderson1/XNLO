//
//  keldysh_gas.hpp
//
//  Modified by Patrick Anderson on 03/09/2015.
//  "keldysh_gas" contains the medium response model.
//

#ifndef __KELDYSH_GAS_HPP_INCLUDED__
#define __KELDYSH_GAS_HPP_INCLUDED__

#include "physics_textbook.hpp"
#include "maths_textbook.hpp"
#include "grid_tw.hpp"
#include <mkl.h>
#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class keldysh_gas {
    // Data
    physics_textbook physics;
    maths_textbook maths;
    grid_tw tw;
    DFTI_DESCRIPTOR_HANDLE ft;

    // Functions
    
public:
    // Data
    double atom_density;
    double U;
    double C_kl;
    double n_star;
    double kappa;
    
    // Functions
    keldysh_gas(double press_, grid_tw tw_, DFTI_DESCRIPTOR_HANDLE ft_);
    ArrayXcd nl_polarization(ArrayXd E_t_);
    ArrayXd ionization_rate(ArrayXd E_t_);
    ArrayXd electron_density(ArrayXd W_t_);
    ArrayXcd current_density(ArrayXd E_t_);
};

#endif
