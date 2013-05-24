/*
 * SpaceFactory.cpp
 *
 * file with functcions that create and provide PsoSpace class
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PsoSpace.hpp"

#include <vector>
#include <string>

namespace PSO {

/*
 * parameterized factory function for making PsoSpace class
 * 
 * @param lowBoundaries - vector of (already checked) values for low boundary
 *                      in each dimension
 * @param high Boundaries - vector of (already checked) values for high boundary
 *                      in each dimension
 * @param boundaryTypes - vector of boundary type indices
 * @return - new PsoSpace object with set dimensions
 * @throws std::invalid_argument - if wrong parameter is provided
 */
PsoSpace* createPsoSpace(std::vector<double>& lowBoundaries,
        std::vector<double>& highBoundaries, std::vector<int>& boundaryTypes,
        std::vector<double>& cellSize);

} // namespace PSO
