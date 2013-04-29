/*
 * GlobalNeighbourhood.cpp
 *
 * a class representing global neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "GlobalNeighbourhood.hpp"

namespace PSO {

GlobalNeighbourhood::GlobalNeighbourhood(const Swarm& _swarm) :
        Neighbourhood(_swarm) {
}

GlobalNeighbourhood::~GlobalNeighbourhood() {
}

void GlobalNeighbourhood::scanNeighbours() {
    // TODO iterate through all the swarm, finding the best particle
}

Particle& GlobalNeighbourhood::findBestNeighbour(int particleIndex) const {
    return bestParticle;
}

} // namespace PSO
