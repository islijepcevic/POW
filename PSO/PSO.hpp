/*
 * PSO.hpp
 *
 * class that implements Particle Swarm Optimization algorithm
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __PSO__
#define __PSO__

#include "PsoParameters.hpp"
#include "AbstractSpace.hpp"
#include "AbstractFitness.hpp"
//#include "Swarm.hpp"
//#include "Neighbourhood.hpp"

#include <mpi.h>
//#include <string>
#include <cstdio>
//#include <boost/mpi.hpp>

namespace PSO {

class PSO {
private:

    // all the parameters
    PsoParameters& params;

    // space
    AbstractSpace& space;

    // fitness function
    AbstractFitness& fitness;

//    // MPI comm world
//    boost::mpi::communicator mpiWorld;
//
//    // swarm of particles
//    Swarm swarm;
//
//    // neighbourhood
//    Neighbourhood* neighbourhood;

    // number of iterations or steps in one run of the PSO
    int totalSteps;

    // number of repetitions of whole PSO algorithm
    int totalRepetitions;

    // inertia parameters of the algorithm
    // (but current inertia is member variable of Swarm)
    double inertiaMax;
    double inertiaMin;

    // output file name
    std::string logFileName;

    // lof file
    FILE* logFile;

    /*
     * method that runs on master process and manages all the work
     */
//    void manager();

    /*
     * method that performs an iteration of one PSO launch
     */
//    void performNextIteration(int step);

    /*
     * method that runs on all other processes (slaves)
     */
//    void worker();

public:

    /*
     * constructor
     * @param _comm - mpi comm world from python
     * @param _params - parameters to the algorithm
     * @param _space - space for the particles
     * @param _fitness - class for the fitness function
     */
    PSO(PsoParameters& _params, AbstractSpace& _space,
            AbstractFitness& _fitness, MPI_Comm _comm);

    /*
     * destructor
     */
    virtual ~PSO();

    /*
     * launches the PSO algorithm
     */
    void launch();


};

} // namespace PSO

#endif // __PSO__
