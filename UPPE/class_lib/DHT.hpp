//
//  DHT.hpp
//
//  Modified by Patrick Anderson on 03/09/2015.
//  "DHT" evaluates the forward and backward discrete Hankel transform. Based on Fisk, Computer
//  Physics Communications, 43 (1987). Complex datatype used here, should really template/overload.
//

#ifndef __DHT_HPP_INCLUDED__
#define __DHT_HPP_INCLUDED__

#include <Eigen/Dense>
#include "maths_textbook.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class DHT {
    // Data
    MatrixXcd H;
    
    // Functions
    
public:
    // Data
    
    // Functions
    DHT();
    DHT(int n_r_, maths_textbook maths_);
    ArrayXcd forward(ArrayXcd f_r_);
    ArrayXcd backward(ArrayXcd f_kr_);
};

#endif
