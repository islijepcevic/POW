/*
 * NeighbourhoodFactory.cpp
 *
 * file with functions that create and provide Neighbourhood classes
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "NeighbourhoodFactory.hpp"

//#include "GlobalNeighbourhood.hpp"
#include "GeographicNeighbourhood.hpp"
#include "IndexedNeighbourhood.hpp"
#include <string>
#include <stdexcept>

namespace PSO {

Neighbourhood* createNeighbourhood(std::string neighbourhoodType,
                                const Swarm& swarm, int nhoodSize) {

    Neighbourhood* nHood;

    int nParticles = swarm.getNoParticles();

    if (neighbourhoodType == "geographic") {
        nHood = new GeographicNeighbourhood(nParticles, nhoodSize);
    } else if (neighbourhoodType == "indexed") {
        nHood = new IndexedNeighbourhood(nParticles, nhoodSize);
//    } else if (neighbourhoodType == "global") {
//        nHood = new GlobalNeighbourhood(swarm);
    } else {
        throw std::invalid_argument("wrong parameter to Neighbourhood factory");
    }

    return nHood;
}

} // namespace PSO
