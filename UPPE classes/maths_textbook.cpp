//
//  maths_textbook.cpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "maths_textbook" is a container for mathematical constants and functions.
//

#include "maths_textbook.hpp"
#include <Eigen/Dense>
#include "IO.hpp"

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor
maths_textbook::maths_textbook() {
    
    // Geometry
    pi = std::acos(-1.0);
    
    // Special functions
    IO file;
    J0_zeros = file.read_double("./input/J0_zeros.bin", 1000, 1);   // From Mathematica
}

//------------------------------------------------------------------------------------------------//
// Trapezoidal integration
double maths_textbook::trapz(ArrayXd x_, ArrayXd y_){
  
    int n_int = x_.rows() - 1;    // intervals
    double temp = (x_.tail(n_int) - x_.head(n_int)).matrix().transpose() *
                  (y_.tail(n_int) + y_.head(n_int)).matrix();
    double output = 0.5 * temp;
    
    return(output);
}

//------------------------------------------------------------------------------------------------//
// Cumulative trapezoidal integration
ArrayXd maths_textbook::cumtrapz(ArrayXd x_, ArrayXd y_){
    
    int n_int = x_.rows() - 1;  // intervals
    ArrayXd temp = 0.5 * (x_.tail(n_int) - x_.head(n_int)) *
                         (y_.tail(n_int) + y_.head(n_int));

    // Cumulative sum
    ArrayXd output = ArrayXd::Zero(n_int + 1);
    output.tail(n_int) = temp;
    for (int ii = 1; ii < n_int + 1; ii++)
        output(ii) += output(ii - 1);
    
    return(output);
}