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

PSO::PSO(PsoSpace* _space, AbstractFitnessProxy& _fitness, MPI_Comm _comm) :
    params(),
    space(_space),
    fitness(_fitness),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(), 
    neighbourhood(),
    totalSteps(),
    inertiaMax(),
    inertiaMin(),
    inertia() {

    if (mpiWorld.rank() != 0) {
//        printf("slave waiting for space\n");
//        broadcast(mpiWorld, space, 0);
//        printf("slave has space\n");
    }
}

PSO::PSO(PsoParameters& _params, PsoSpace* _space,
            AbstractFitnessProxy& _fitness, MPI_Comm _comm) :
    params(_params),
    space(_space),
    fitness(_fitness),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(),
    neighbourhood(NULL),
    totalSteps(params.getIntParam("max_steps")),
    totalRepetitions(params.getIntParam("repeat")),
    inertiaMax(params.getDoubleParam("inertia_max")),
    inertiaMin(params.getDoubleParam("inertia_min")),
    inertia(inertiaMax) {

    // this constructor is called from rank 0 anyway
    if (mpiWorld.rank() == 0) {

//        printf("master sending space\n");
//        broadcast(mpiWorld, space, 0);
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

    // loop that repeats executing PSO algorithm
    for (int repeatNo = 0; repeatNo < totalRepetitions; repeatNo++) {
        // print using observers
        for (std::list<AbstractPrinter*>::const_iterator printIterator
                = printers.begin(); printIterator != printers.end();
                printIterator++) {
            (*printIterator)->printRepetitionStart(*this);
        }

        // seed all the particles in the swarm
        swarm.seedParticles();

        // main loop for one PSO launch
        for (int step = 0; step < totalSteps; step++) {

            // rescale inertia factor
            inertia = inertiaMax
                - (double)step / totalSteps * (inertiaMax - inertiaMin);

            // update neighbourhood
            neighbourhood->scanNeighbours(swarm);

        }
    }

}

/*
 * main code for every other node
 */
void PSO::worker() {
}

} // namespace PSO
