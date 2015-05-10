//
//  maths_textbook.cpp
//
//  Modified by Patrick Anderson on 07/05/2015.
//  "maths_textbook" is a container for mathematical constants.
//

#include "maths_textbook.hpp"
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor

maths_textbook::maths_textbook() {
    
    // Geometry
    pi = std::acos(-1.0);
    
}

//------------------------------------------------------------------------------------------------//
// Trapezoidal integration, vectorized

double maths_textbook::trapz(ArrayXd x_, ArrayXd y_){
  
    int N = x_.rows() - 1;
    ArrayXd x_temp = x_.tail(N) - x_.head(N);
    ArrayXd y_temp = y_.tail(N) + y_.head(N);
    
    return(0.5 * (x_temp * y_temp).sum());
    
}
