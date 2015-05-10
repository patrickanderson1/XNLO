//
//  text.hpp
//
//  Modified by Patrick Anderson on 09/05/2015.
//  "text" is a tab-delimited file.
//

#ifndef __TEXT_HPP_INCLUDED__
#define __TEXT_HPP_INCLUDED__

#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition

class text {
    
public:
    
    //Data
    
    //Functions
    text(ArrayXXd data, char* path);
    
};

#endif
