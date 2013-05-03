/*
 * PSO.cpp
 *
 * class that implements Particle Swarm Optimization algorithm
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PSO.hpp"

namespace PSO {

PSO::PSO(MPI_Comm _comm, BaseParameters& _params, AbstractSpace& _space,
        AbstractFitness& _fitness) :
    comm_world(_comm), params(_params), space(_space), fitness(_fitness),
    Swarm(params.getIntParam("n_particles", space),
    maxSteps(params.getIntParam("max_steps")),
    nAlgRepetitions(params.getIntParams("repeat")) {
}

virtual ~PSO::PSO() {
}

void PSO::launch() {
    //TODO
}

// TODO methods for master/slave

} // namespace PSO
