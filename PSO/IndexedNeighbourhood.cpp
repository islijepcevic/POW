/*
 * IndexedNeighbourhood.cpp
 *
 * a class representing indexed local neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "IndexedNeighbourhood.hpp"

namespace PSO {

IndexedNeighbourhood::IndexedNeighbourhood(const Swarm& _swarm) :
        Neighbourhood(_swarm) {
}

IndexedNeighbourhood::~IndexedNeighbourhood() {
}

void IndexedNeighbourhood::scanNeighbours() {
    // TODO iterate through all the swarm, finding the best particle
}

Particle& IndexedNeighbourhood::findBestNeighbour(int particleIndex) const {
    // TODO
}

} // namespace PSO
