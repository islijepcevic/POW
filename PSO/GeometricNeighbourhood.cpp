/*
 * GeometricNeighbourhood.cpp
 *
 * a class representing geometric local neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "GeometricNeighbourhood.hpp"

namespace PSO {

GeometricNeighbourhood::GeometricNeighbourhood(const Swarm& _swarm) :
        Neighbourhood(_swarm) {
}

GeometricNeighbourhood::~GeometricNeighbourhood() {
}

void GeometricNeighbourhood::scanNeighbours() {
    // TODO iterate through all the swarm, finding the best particle
}

Particle& GeometricNeighbourhood::findBestNeighbour(int particleIndex) const {
    // TODO
}

} // namespace PSO
