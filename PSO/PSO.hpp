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

#include "BaseParameters.hpp"
#include "AbstractSpace.hpp"
#include "AbstractFitness.hpp"
#include "Swarm.hpp"
#include "Neighbourhood.hpp"

#include <mpi.h>
#include <string>
#include <cstdio>

namespace PSO {

class PSO {
private:

    // all the parameters
    BaseParameters& params;

    // space
    AbstractSpace& space;

    // fitness function
    AbstractFitness& fitness;

    // swarm of particles
    Swarm swarm;

    // neighbourhood
    Neighbourhood* neighbourhood;

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

    // MPI comm world
    MPI_Comm commWorld;

    // rank of MPI process
    int mpiRank;

    // number of MPI processes
    int mpiSize;

    // TODO make methods for master and parallel slaves

public:

    /*
     * constructor
     * @param _comm - mpi comm world from python
     * @param _params - parameters to the algorithm
     * @param _space - space for the particles
     * @param _fitness - class for the fitness function
     */
    PSO(BaseParameters& _params, AbstractSpace& _space,
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
