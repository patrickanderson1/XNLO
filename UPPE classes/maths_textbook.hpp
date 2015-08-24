//
//  maths_textbook.hpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "maths_textbook" is a container for mathematical constants and functions.
//

#ifndef __MATHS_TEXTBOOK_HPP_INCLUDED__
#define __MATHS_TEXTBOOK_HPP_INCLUDED__

#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class maths_textbook {
    
public:
    // Data
    double pi;
    ArrayXd J0_zeros;
    
    // Functions
    maths_textbook();
    double trapz(ArrayXd x_, ArrayXd y_);
    ArrayXd cumtrapz(ArrayXd x_, ArrayXd y_);
};

#endif
