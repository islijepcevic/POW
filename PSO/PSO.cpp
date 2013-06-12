/*
 * PSO.cpp
 *
 * class that implements Particle Swarm Optimization algorithm
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PSO.hpp"

// temporary include
#include <cstdio>
#include <iostream>
#include "NeighbourhoodFactory.hpp"

namespace PSO {

PSO::PSO(PsoSpace* _space, AbstractFitness& _fitness, MPI_Comm _comm) :
    params(),
    space(_space),
    fitness(&_fitness),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(), 
    neighbourhood(NULL),
    totalSteps(),
    inertiaMax(),
    inertiaMin() {

    if (mpiWorld.rank() != 0) {
//        printf("slave waiting for space\n");
//        broadcast(mpiWorld, *space, 0);
//        printf("slave has space\n");
    }
}

PSO::PSO(PsoParameters& _params, PsoSpace* _space,
            AbstractFitness& _fitness, MPI_Comm _comm) :
    params(_params),
    space(_space),
    fitness(&_fitness),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(),
    neighbourhood(NULL),
    totalSteps(params.getIntParam("max_steps")),
    totalRepetitions(params.getIntParam("repeat")),
    inertiaMax(params.getDoubleParam("inertia_max")),
    inertiaMin(params.getDoubleParam("inertia_min")) {

    // this constructor is called from rank 0 anyway
    if (mpiWorld.rank() == 0) {

//        printf("master sending space\n");
//        broadcast(mpiWorld, *space, 0);
//        printf("master sent space\n");

        swarm = Swarm(params.getIntParam("n_particles"), *space);

        neighbourhood = createNeighbourhood(
             params.getStringParam("neigh_type"),
             swarm,
             params.getIntParam("neigh_size")
        );

        // mpi send skeletons
    }
}

PSO::~PSO() {
    // space and fitness will be freed in Python (automatically)
    if (neighbourhood != NULL) {
        delete neighbourhood;
    }
}

void PSO::registerPrinterObserver(AbstractPrinter* printer) {
    printers.push_back(printer);
}

/*
 * main launch
 *
 * RANK IS ONLY PARAMETER HERE FOR TESTING PURPOSES - REMOVE IT WHEN REAL
 * MPI TAKES THE PLACE
 */
void PSO::launch() {

    // print using observers
    for (std::list<AbstractPrinter*>::const_iterator printIterator
            = printers.begin(); printIterator != printers.end();
            printIterator++) {
        (*printIterator)->printRepetitionStart(*this);
    }

    printf("%d; nodim %d\n", mpiWorld.rank(), space->getNoDimensions());
    mpiWorld.barrier();

    if (mpiWorld.rank() == 0) {
        manager();
    } else {
        worker();
    }

}

/*
 * main code for rank 0
 */
void PSO::manager() {

//
//    // synchronize (barrier, broadcast), maybe NOT; TODO
//
//    // loop that repeats executing PSO algorithm
//    for (int repeatNo = 0; repeatNo < totalRepetitions; repeatNo++) {
//        printf("\n> REPETITION %d\n", repeatNo + 1);
//
//    // seed all the particles in the swarm
//    // init local variables
//    double inertiaMax = params.getDoubleParam("inertia_max");
//    double inertiaMin = params.getDoubleParam("inertia_min");

        swarm.seedParticles();
        // set best values to check neighborhoods
        for (int i = 0; i < swarm.getNoParticles(); i++) {
            Particle& p( swarm.getParticle(i) );
            p.bestValue = (double)i;
            //std::cout << p;
        }

        printf("SCANNING NHOOD\n");
        neighbourhood->scanNeighbours(swarm);

        // anyway - this loop is to be removed, despite weird errors
        for (int i = 0; i < swarm.getNoParticles(); i++) {
            Particle& p = swarm.getParticle(i);
            std::cout << "PARTICLE" << std::endl;
            std::cout << p; // THIS WORKS
            const Particle& pbest = neighbourhood->findBestNeighbour(i);
            std::cout << "NEIGHBOUR" << std::endl;
            std::cout << pbest;

            //std::cout << swarm.getParticle(i); // already printed
            // THE LINE ABOVE WAS VERY PROBLEMATIC
            // compiling PSO_wrap.cxx:
            //      undefined symbol: _ZNK3PSO5Swarm11getParticleEi
        }

//        // main loop for one PSO launch
//        for (int step = 0; step < totalSteps; step++) {
//            // do the work
//            performNextIteration(step);
//        }
//    }
//
//    // close log file
//    fclose(logFile);
//}
//
///*
// * this is still the work of root node (rank 0)
// */
//void PSO::performNextIteration(int step) {
//
//    // rescale inertia factor
//    swarm.inertia = inertiaMax
//        - (double)step / totalSteps * (inertiaMax - inertiaMin);
//
//    // update neighbourhood
//    neighbourhood->scanNeighbours(swarm);
//
//    // for every particle, send data to worker()
//    for (int indexParticle = 0; indexParticle = swarm.getNoParticles();
//            indexParticle++) {
//        //...
//    }
//
//    // gather all data
//
//    // write all to the log
}

/*
 * main code for every other node
 */
void PSO::worker() {
}

} // namespace PSO
