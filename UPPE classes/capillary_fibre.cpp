//
//  capillary_fibre.hpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "capillary_fibre" describes the dimensions and dispersion properties of a dielectric capillary
//  type fibre.
//

#include "capillary_fibre.hpp"
#include <Eigen/Dense>
#include "grid_tw.hpp"
#include "grid_rkr.hpp"
#include "physics_textbook.hpp"
#include "maths_textbook.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor
capillary_fibre::capillary_fibre(double Z_, grid_rkr rkr_, grid_tw tw_, physics_textbook physics_,
                                 maths_textbook maths_) {

    Z = Z_;
    R = rkr_.R;
    n_glass = 1.47738;
    
    // Complex modal propagation constants (Marcatili and Schmeltzer, 1964)
    ArrayXd k_w_active = tw_.w_active / physics_.c;
    beta = ArrayXXd::Zero(tw_.n_active, rkr_.n_m);
    alpha = ArrayXXd::Zero(tw_.n_active, rkr_.n_m);
    for (int ii = 0; ii < rkr_.n_m; ii++) {
        // Dispersion
        beta.col(ii) = k_w_active * (1.0 - (0.5 * ((maths_.J0_zeros(ii) * physics_.c /
                                                    (R * tw_.w_active)).pow(2.0))));
        // Loss
        alpha.col(ii) = (1.0 / R) * ((maths_.J0_zeros(ii) * physics_.c) /
                                   (R * tw_.w_active)).pow(2.0) *
                        ((1.0 + std::pow(n_glass, 2.0)) /
                         (2.0 * std::sqrt(std::pow(n_glass, 2.0) - 1.0)));
    }
}

