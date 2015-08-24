//
//  IO.hpp
//
//  Modified by Patrick Anderson on 24/08/2015.
//  "IO" objects enable reading/writing of binary files to/from Eigen arrays.
//

#ifndef __IO_HPP_INCLUDED__
#define __IO_HPP_INCLUDED__

#include <Eigen/Dense>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class definition
//------------------------------------------------------------------------------------------------//
class IO {
    
public:
    // Data
    
    // Functions
    Array<unsigned short, Dynamic, Dynamic> read_uint16(const char* path_, int N_row_, int N_col_);
    ArrayXXi read_int(const char* path_, int N_row_, int N_col_);
    ArrayXXd read_double(const char* path_, int N_row_, int N_col_);
    void write_double(const char* path_, ArrayXXd input_, int N_row_, int N_col_);
};

#endif
