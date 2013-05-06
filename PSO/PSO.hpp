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

#include <mpi.h>
#include <string>

namespace PSO {

class PSO {
private:

    // MPI comm world
    MPI_Comm comm_world;

    // all the parameters
    BaseParameters& params;

    // space
    AbstractSpace& space;

    // fitness function
    AbstractFitness& fitness;

    // swarm of particles
    Swarm swarm;

    // number of iterations or steps in one run of the PSO
    int maxSteps;

    // number of repetitions of whole PSO algorithm
    int nAlgRepetitions;

    // inertia at current step
    double inertia;

    // output file name
    std::string outFileName;

    // TODO make methods for master and parallel slaves

public:

    /*
     * constructor
     * @param _comm - mpi comm world from python
     * @param _params - parameters to the algorithm
     * @param _space - space for the particles
     * @param _fitness - class for the fitness function
     */
    PSO(MPI_Comm _comm, BaseParameters& _params, AbstractSpace& _space,
            AbstractFitness& _fitness);

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
