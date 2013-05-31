/*
 * GlobalNeighbourhood.cpp
 *
 * a class representing global neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "GlobalNeighbourhood.hpp"

#include "Swarm.hpp"

namespace PSO {

GlobalNeighbourhood::GlobalNeighbourhood() {
}

GlobalNeighbourhood::~GlobalNeighbourhood() {
}

void GlobalNeighbourhood::scanNeighbours(const Swarm& swarm) {
    // TODO iterate through all the swarm, finding the best particle
}

const Particle& GlobalNeighbourhood::findBestNeighbour(int particleIndex) const
{
    return bestParticle;
}

} // namespace PSO
