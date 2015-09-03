//
//  main.cpp
//
//  Modified by Patrick Anderson on 03/09/2015.
//  Test enviroment for UPPE codes.
//

#include <mpi.h>
#include "./class_lib/maths_textbook.hpp"
#include "./class_lib/physics_textbook.hpp"
#include <mkl.h>
#include "./class_lib/DHT.hpp"
#include "./class_lib/grid_rkr.hpp"
#include "./class_lib/grid_tw.hpp"
#include "./class_lib/laser_pulse.hpp"
#include "./class_lib/capillary_fibre.hpp"
#include "./class_lib/keldysh_gas.hpp"
#include <Eigen/Dense>
#include "./class_lib/IO.hpp"

using namespace Eigen;

int main(int argc, char** argv){
    
    // MPI
    int this_process;
    int total_processes;
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_process);
    
    //--------------------------------------------------------------------------------------------//
    // 1. Program input
    //--------------------------------------------------------------------------------------------//
    int n_z = 50;
    int n_r = 20;
    int n_m = 20;
    
    int n_t = 4096;
    double T = 500.0e-15;
    double w_active_min = 2.0e14;
    double w_active_max = 8.0e15;
    
    double Z = 5.0e-3;
    double R = 75.0e-6;
    
    double press = 100.0e-3;
    
    double p_av = 1.0;
    double rep = 1.0e3;
    double fwhm = 40e-15;
    double l_0 = 800e-9;
    double ceo = 0.0;
    double waist = 48.0e-6;
    
    //--------------------------------------------------------------------------------------------//
    // 2. Constructors
    //--------------------------------------------------------------------------------------------//
    // General
    maths_textbook maths;
    physics_textbook physics;
    
    MKL_LONG dimensions = 1;
    MKL_LONG length = n_t;
    double scale = 1.0 / n_t;
    DFTI_DESCRIPTOR_HANDLE ft;
    DftiCreateDescriptor(&ft, DFTI_DOUBLE, DFTI_COMPLEX, dimensions, length);
    DftiSetValue(ft, DFTI_BACKWARD_SCALE, scale);
    DftiCommitDescriptor(ft);
    
    DHT ht(n_r, maths);
    
    // Grids
    grid_rkr rkr(n_r, R, n_m, maths);
    grid_tw tw(n_t, T, w_active_min, w_active_max, maths);
    
    // Physical
    laser_pulse laser(p_av, rep, fwhm, l_0, ceo, waist, tw, rkr, ft, ht);
    capillary_fibre capillary(Z, rkr, tw, physics, maths);
    keldysh_gas gas(press, tw, ft);
        
    //--------------------------------------------------------------------------------------------//
    // 3. Propagation
    //--------------------------------------------------------------------------------------------//
    // Main loop
    double dz = capillary.Z / n_z;
    for (int ii = 1; ii < n_z + 1; ii++) {
        std::cout << "Propagation step: " << ii << std::endl;
        laser.propagate(dz, capillary, gas);
    }
    
    // Output
    IO file;
    file.write_double("./output/A_w_R.bin", laser.A_w_active.real(), tw.n_active, rkr.n_m);
    file.write_double("./output/A_w_I.bin", laser.A_w_active.imag(), tw.n_active, rkr.n_m);
    file.write_double("./output/w_active.bin", tw.w_active, tw.n_active, 1);

    // Clean up
    DftiFreeDescriptor(&ft);
    MPI_Finalize();
}



