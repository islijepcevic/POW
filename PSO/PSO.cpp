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

PSO::PSO(MPI_Comm _comm) :
    params(),
    space(),
    fitness(NULL),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(), 
    neighbourhood(NULL),
    totalSteps(),
    inertiaMax(),
    inertiaMin() {
}

PSO::PSO(PsoParameters& _params, PsoSpace* _space,
            AbstractFitness& _fitness, MPI_Comm _comm) :
    params(_params),
    space(*_space),
    fitness(&_fitness),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(),
//    neighbourhood(NULL),
    totalSteps(params.getIntParam("max_steps")),
    totalRepetitions(params.getIntParam("repeat")),
    inertiaMax(params.getDoubleParam("inertia_max")),
    inertiaMin(params.getDoubleParam("inertia_min")) {

    // this constructor is called from rank 0 anyway
    if (mpiWorld.rank() == 0) {
        swarm = Swarm(params.getIntParam("n_particles"), space);

//        neighbourhood = createNeighbourhood(
//            params.getStringParam("neigh_type"),
//            swarm
//        );
    }
}

PSO::~PSO() {
    // space and fitness will be freed in Python (automatically)
//    free(neighbourhood);
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

    // some prints only for the test
    printf("this is Hello from c++ PSO.launch()\n");
    // print using observers
    for (int i = 0; i < printers.size(); i++) {
        (printers[i])->printRepetitionStart(*this);
    }

    Particle p;
    p.currentPosition.push_back(6.0);
    p.currentPosition.push_back(6.0);
    p.currentVelocity.push_back(10);
    p.currentVelocity.push_back(10);

    if (mpiWorld.rank() == 0) {
        printf("no dimensions: %d\n", space.getNoDimensions());
        printf("PARTICLE BEFORE; p: %lf %lf; v: %lf %lf\n",
            p.currentPosition[0], p.currentPosition[1],
            p.currentVelocity[0], p.currentVelocity[1]);
        space.checkBoundaries(p);
        printf("PARTICLE AFTER; p: %lf %lf; v: %lf %lf\n",
            p.currentPosition[0], p.currentPosition[1],
            p.currentVelocity[0], p.currentVelocity[1]);
    }


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
        // anyway - this loop is to be removed, despite weird errors
        for (int i = 0; i < swarm.getNoParticles(); i++) {
            Particle& p = swarm.getParticle(i);
            std::cout << p; // THIS WORKS
            //std::cout << swarm.getParticle(i);
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
//    neighbourhood.scanNeighbours();
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
