//
//  main.cpp
//
//  Modified by Patrick Anderson on 07/05/2015.
//  Test environment for single atom codes.
//


#include <mpi.h>
#include "./class_lib/grid_xkx.hpp"
#include "./class_lib/grid_tw.hpp"
#include "./class_lib/laser_pulse.hpp"
#include <limits>
#include "./class_lib/text.hpp"
#include "./class_lib/Schrodinger_atom_1D.hpp"

int main(int argc, char** argv){
    
    // MPI
    int this_node;
    int total_nodes;
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_nodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_node);
    
    // Input
    int atoms_per_worker = 2;
    int total_atoms = atoms_per_worker * (total_nodes - 1);
    
    // Grids
    grid_xkx xkx(total_atoms, 0, 100e-6);
    grid_tw tw(std::pow(2.0, 18), -100e-15, 100e-15);
    
    // Control
    if (this_node == 0) {
        
        // Field
        double ROC = std::numeric_limits<double>::max();
        laser_pulse pulse(0.18, 1000, 15e-15, 795e-9, 0, 42e-6, ROC, xkx, tw);
        
        // Send
        for (int ii = 1; ii < total_nodes; ii++) {
            
            MPI_Send(pulse.E.block(0, atoms_per_worker * (ii - 1), tw.N_t, atoms_per_worker).data(),
                     tw.N_t * atoms_per_worker, MPI::DOUBLE, ii, 1, MPI_COMM_WORLD);
            
        }
        
        // Receive
        ArrayXXd dipole = ArrayXXd::Zero(tw.N_t, total_atoms);
        
        for (int jj = 1; jj < total_nodes; jj++) {
            
            // Request
            bool send = true;
            MPI_Send(&send, 1, MPI::BOOL, jj, 1, MPI_COMM_WORLD);
            
            MPI_Recv(dipole.block(0, atoms_per_worker * (jj - 1), tw.N_t, atoms_per_worker).data(),
                     tw.N_t * atoms_per_worker, MPI::DOUBLE, jj, 1, MPI_COMM_WORLD, &status);
            
        }
        
        // Output
        text output(dipole, "./output/dipole.txt");
        text output2(tw.w, "./output/w.txt");

    }
    
    // Worker
    if (this_node != 0) {
     
        // Receive
        ArrayXXd E = ArrayXXd::Zero(tw.N_t, atoms_per_worker);
        MPI_Recv(E.data(), E.rows() * E.cols(), MPI::DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
        
        // Single atom calculations
        ArrayXXd dipole = ArrayXXd::Zero(tw.N_t, atoms_per_worker);
        Schrodinger_atom_1D atom(1.45);
        
        for (int ii = 0; ii < atoms_per_worker; ii++) {
            
            dipole.col(ii) = atom.get_dipole(tw.N_t, tw.dt, E.col(ii));
            
        }
        
        // Send
        bool send;
        MPI_Recv(&send, 1, MPI::BOOL, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Send(dipole.data(), tw.N_t * atoms_per_worker, MPI::DOUBLE, 0, 1, MPI_COMM_WORLD);
        
    }
    
    // Clean up
    MPI_Finalize();
    
}

