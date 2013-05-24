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

PsoSpace createPsoSpace(std::vector<double>& lowBoundaries,
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
        printf("C %d\n", i);
        printf("D %d %lf\n", i, cellSize[i]); // I OVO JE GRESKA
        // TU ISPOD JE GRESKA

        double size = cellSize[i];
        printf("E %d\n", i);
        double dsize = dim->getSize();
        printf("F %d\n", i);
        if (size != dim->getSize()) {
            throw std::invalid_argument("cell size is wrong");
        }
        printf("G %d\n", i);

        dimensions.push_back(dim);
    }
    printf("Z\n");

    PsoSpace space(dimensions);

    return space;
}

} // namespace PSO
