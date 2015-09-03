//
//  IO.hpp
//
//  Modified by Patrick Anderson on 03/09/2015.
//  "IO" objects enable reading/writing of binary files to/from eigen arrays.
//

#include "IO.hpp"
#include <Eigen/Dense>
#include <fstream>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor
IO::IO() {  }

//------------------------------------------------------------------------------------------------//
// Read from binary file to N_col_ by N_row_ Eigen array
// uint16
Array<unsigned short, Dynamic, Dynamic> IO::read_uint16(const char* path, int N_row_, int N_col_) {
    
    Array<unsigned short, Dynamic, Dynamic> output(N_row_, N_col_);
    std::ifstream fs(path, std::ios_base::in | std::ios_base::binary);
    fs.read((char*) output.data(), N_row_ * N_col_ * sizeof(unsigned short));
    fs.close();
    
    return(output);
}

// int
ArrayXXi IO::read_int(const char* path, int N_row_, int N_col_) {
    
    ArrayXXi output(N_row_, N_col_);
    std::ifstream fs(path, std::ios_base::in | std::ios_base::binary);
    fs.read((char*) output.data(), N_row_ * N_col_ * sizeof(int));
    fs.close();
    
    return(output);
}

// double
ArrayXXd IO::read_double(const char* path, int N_row_, int N_col_) {
    
    ArrayXXd output(N_row_, N_col_);
    std::ifstream fs(path, std::ios_base::in | std::ios_base::binary);
    fs.read((char*) output.data(), N_row_ * N_col_ * sizeof(double));
    fs.close();
    
    return(output);
}

//------------------------------------------------------------------------------------------------//
// Write to binary file from N_col_ by N_row_ Eigen array
// double
void IO::write_double(const char* path, ArrayXXd input, int N_row_, int N_col_) {
    
    std::ofstream fs(path, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
    fs.write((char*) input.data(), N_row_ * N_col_ * sizeof(double));
    fs.close();
}

