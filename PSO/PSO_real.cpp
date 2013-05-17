/*
 * PSO_real.hpp
 *
 * this is the PSO class skeleton with most of the things added and the
 * implementation started.
 *
 * new PSO class has been created and things will be added iteratively
 * (from here)
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PSO.hpp"

#include "NeighbourhoodFactory.hpp"

namespace PSO {

PSO::PSO(BaseParameters& _params, AbstractSpace& _space,
            AbstractFitness& _fitness, MPI_Comm _comm) :
    params(_params),
    space(_space),
    fitness(_fitness),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(),
    neighbourhood(NULL),
    totalSteps(params.getIntParam("max_steps")),
    totalRepetitions(params.getIntParams("repeat")),
    inertiaMax(params.getDoubleParam("inertia_max"),
    inertiaMin(params.getDoubleParam("inertia_min"),
    logFileName(params.getStringParams("output_file")),
    logFile(NULL) {

    if (mpiWorld.rank() == 0) {
        swarm = Swarm(params.getIntParam("n_particles"), space);

        neighbourhood = createNeighbourhood(
            params.getStringParams("neigh_type"),
            swarm
        );
    }
}

virtual ~PSO::PSO() {
    free(neighbourhood);
}

/*
 * main launch
 */
void PSO::launch() {

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

    // open log file
    logFile = fopen(logFileName.c_str(), "w");
    if (logFile == NULL) {
        throw std::bad_alloc("could not open log file");
    }

    // synchronize (barrier, broadcast), maybe NOT; TODO

    // loop that repeats executing PSO algorithm
    for (int repeatNo = 0; repeatNo < totalRepetitions; repeatNo++) {
        printf("\n> REPETITION %d\n", repeatNo + 1);

    // seed all the particles in the swarm
    // init local variables
    double inertiaMax = params.getDoubleParam("inertia_max");
    double inertiaMin = params.getDoubleParam("inertia_min");

        swarm.seedParticles();

        // main loop for one PSO launch
        for (int step = 0; step < totalSteps; step++) {
            // do the work
            performNextIteration(step);
        }
    }

    // close log file
    fclose(logFile);
}

/*
 * this is still the work of root node (rank 0)
 */
void PSO::performNextIteration(int step) {

    // rescale inertia factor
    swarm.inertia = inertiaMax
        - (double)step / totalSteps * (inertiaMax - inertiaMin);

    // update neighbourhood
    neighbourhood.scanNeighbours();

    // for every particle, send data to worker()
    for (int indexParticle = 0; indexParticle = swarm.getNoParticles();
            indexParticle++) {
        //...
    }

    // gather all data

    // write all to the log
}

/*
 * main code for every other node
 */
void PSO::worker() {
}

} // namespace PSO
