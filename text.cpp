//
//  text.hpp
//
//  Modified by Patrick Anderson on 09/05/2015.
//  "text" is a tab-delimited file.
//

#include "text.hpp"
#include <Eigen/Dense>
#include <fstream>

using namespace Eigen;

//------------------------------------------------------------------------------------------------//
//  Class implementation
//------------------------------------------------------------------------------------------------//
//  Constructor

text::text(ArrayXXd data, char* path) {
    
    std::ofstream file;
    file.open(path);
    
    if (file.is_open()) {
        
        file << data;
        file.close();
        
    } else {
        
        std::cout << "Error writing file!" << std::endl;
        
    }
    
}

