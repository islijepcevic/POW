/*
 * NeighbourhoodFactory.hpp
 *
 * file with functions that create and provide Neighbourhood classes
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "Neighbourhood.hpp"

#include "Swarm.hpp"
#include <string>

namespace PSO {

/*
 * parameterized factory function for Neighbourhood family of classes.
 * this is to be changed if new neighbourhood type should be created
 * @param neighbourhoodType - type of the Neighbourhood to be created.
 *     Currently, it supports parameters "global", "geographic" and "indexed"
 *     for GlobalNeighbourhood, GeometricNeighbourhood and IndexedNeighbourhood
 *     classes respectively.
 * @param swarm - reference to swarm, needed for all Neighbourhoods
 * @return - pointer to created Neighbourhood
 * @throws std::invalid_argument - if wrong parameter is provided
 */
Neighbourhood* createNeighbourhood(std::string neighbourhoodType,
                                    const Swarm& swarm);

} // namespace PSO
