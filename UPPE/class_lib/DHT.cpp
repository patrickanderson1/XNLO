//
//  DHT.hpp
//
//  Modified by Patrick Anderson on 03/09/2015.
//  "DHT" evaluates the forward and backward discrete Hankel transform. Based on Fisk, Computer
//  Physics Communications, 43 (1987). Complex datatype used here, should really template/overload.
//

#include "DHT.hpp"
#include "maths_textbook.hpp"

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Default constructor
DHT::DHT() {  }

//------------------------------------------------------------------------------------------------//
//  Parameterized constructor
DHT::DHT(int n_r_, maths_textbook maths_) {
    
    // Transformation matrix
    MatrixXd temp_1 = MatrixXd::Zero(n_r_, n_r_);
    for (int ii = 0; ii < n_r_; ii++) {
        for (int jj = 0; jj < n_r_; jj++) {
            temp_1(ii, jj) = (2.0 / maths_.J0_zeros(n_r_)) *
                             (j0(maths_.J0_zeros(jj) * maths_.J0_zeros(ii) /
                                 maths_.J0_zeros(n_r_)) /
                              std::pow(j1(maths_.J0_zeros(jj)), 2.0));
        }
    }
    H = temp_1.cast<std::complex<double> >();
}

//------------------------------------------------------------------------------------------------//
//  Forward transform
ArrayXcd DHT::forward(ArrayXcd f_r_) {
    
    ArrayXcd output = H * f_r_.matrix();
    
    return(output);
}

//------------------------------------------------------------------------------------------------//
//  Backward transform
ArrayXcd DHT::backward(ArrayXcd f_kr_) {
    
    ArrayXcd output = H * f_kr_.matrix();
    
    return(output);
}