/**
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
#include "PsoSpace.hpp"
#include "AbstractFitnessProxy.hpp"
#include "AbstractPrinter.hpp"
#include "Swarm.hpp"
#include "Neighbourhood.hpp"

#include <mpi.h>
#include <list>
//#include <string>
#include <boost/mpi.hpp>

namespace PSO {

/**
 * a class that implements PSO algorithm
 */
class PSO {
private:

    // all the parameters
    PsoParameters params;

    // space
    PsoSpace* space;

    // fitness function
    AbstractFitnessProxy& fitness;

    // MPI comm world
    boost::mpi::communicator mpiWorld;

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

    // inertia at current step
    // it would be conceptually more precise to make it a member of Swarm, but
    // this is easier to mantain
    double inertia;

    // list of printer observers
    std::list<AbstractPrinter*> printers;

/*********************************************************************
 * METHODS
 *******************************************************************/

    /**
     * method that runs on master process and manages all the work
     */
    void manager();

    /**
     * method that runs on all other processes (slaves)
     */
    void worker();

public:

    /**
     * minimal constructor - used for slave nodes
     */
    PSO(PsoSpace* _space, AbstractFitnessProxy& _fitness, MPI_Comm _comm);

    /**
     * constructor - used for master node
     * @param _comm - mpi comm world from python
     * @param _params - parameters to the algorithm
     * @param _space - space for the particles
     * @param _fitness - class for the fitness function
     */
    PSO(PsoParameters& _params, PsoSpace* _space,
            AbstractFitnessProxy& _fitness, MPI_Comm _comm);

    /**
     * destructor
     */
    virtual ~PSO();

    /**
     * method that registers a printer observer
     * @param printer - an instance of some printer class
     */
    void registerPrinterObserver(AbstractPrinter* printer);

    /**
     * launches the PSO algorithm
     */
    void launch();

};

} // namespace PSO

#endif // __PSO__
