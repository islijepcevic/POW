/*
 * NeighbourhoodFactory.cpp
 *
 * file with functions that create and provide Neighbourhood classes
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "NeighbourhoodFactory.hpp"

#include "GlobalNeighbourhood.hpp"
#include "GeometricNeighbourhood.hpp"
#include "IndexedNeighbourhood.hpp"
#include <stdexcept>

Neighbourhood* createNeighbourhood(std::string neighbourhoodType,
                                const Swarm& swarm) {

    Neighbourhood* nHood;

    if (neighbourhoodType == "global") {
        nHood = new GlobalNeighbourhood(swarm);
    } else if (neighbourhoodType == "indexed") {
        nHood = new IndexedNeighbourhood(swarm);
    } else if (neighbourhoodType == "geographic") {
        nHood = new GeometricNeighbourhood(swarm);
    } else {
        throw std::invalid_argument("wrong parameter to Neighbourhood factory");
    }

    return nHood;
}
