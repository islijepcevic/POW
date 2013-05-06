/*
 * PSO.cpp
 *
 * class that implements Particle Swarm Optimization algorithm
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
    swarm(params.getIntParam("n_particles", space),
    neighbourhood(NULL),
    totalSteps(params.getIntParam("max_steps")),
    totalRepetitions(params.getIntParams("repeat")),
    inertiaMax(params.getDoubleParam("inertia_max"),
    inertiaMin(params.getDoubleParam("inertia_min"),
    logFileName(params.getStringParams("output_file")),
    logFile(NULL),
    commWorld(_comm), {

    MPI_Comm_size(commWorld, &mpiSize);
    MPI_Comm_rank(commWorld, &mpiRank);

    neighbourhood = createNeighbourhood(
        params.getStringParams("neigh_type"),
        swarm
    );
}

virtual ~PSO::PSO() {
    free(neighbourhood);
}

void PSO::launch() {
    //TODO
}

// TODO methods for master/slave

} // namespace PSO
