/*
 * SpaceFactory.cpp
 *
 * file with functcions that create and provide PsoSpace class
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "SpaceFactory.hpp"

#include "PeriodicDimension.hpp"
#include "ReflexiveDimension.hpp"
#include <stdexcept>

#include <cstdio>

#define PERIODIC 0
#define REFLEXIVE 1

namespace PSO {

PsoSpace* createPsoSpace(std::vector<double>& lowBoundaries,
        std::vector<double>& highBoundaries, std::vector<int>& boundaryTypes,
        std::vector<double>& cellSize) {

    int noDimensions = lowBoundaries.size();
    std::vector<Dimension*> dimensions;

    for (int i = 0; i < noDimensions; i++) {
        double low = lowBoundaries[i];
        double high = highBoundaries[i];
        int type = boundaryTypes[i];

        Dimension* dim;

        if (type == PERIODIC) {
            dim = new PeriodicDimension(low, high);
        } else if (type == REFLEXIVE) {
            dim = new ReflexiveDimension(low, high);
        } else {
            throw std::invalid_argument("wrong boundary type for dimension");
        }

        double size = cellSize[i];
        double dsize = dim->getSize();
        if (size != dim->getSize()) {
            throw std::invalid_argument("cell size is wrong");
        }

        dimensions.push_back(dim);
    }

    PsoSpace *space = new PsoSpace(dimensions);
    return space;
}

} // namespace PSO
