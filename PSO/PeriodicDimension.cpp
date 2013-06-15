/*
 * PeriodicDimension.cpp
 *
 * Subclass of Dimension with periodic boundary condition
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PeriodicDimension.hpp"

#include <cmath>

namespace PSO {

PeriodicDimension::PeriodicDimension(const double _lower,
                                    const double _higher) :
    Dimension(_lower, _higher) {
}

PeriodicDimension::~PeriodicDimension() {
}

std::pair<double, double> PeriodicDimension::checkBoundaries(double position,
                                                        double velocity) const {

    // scale boundaries such that lower bound starts from zero
    position -= lowerBound;
    
    // apply the boundary conditions
    position = fmod(position, size);
    // because of c++ weird modulo, move this to [0, 2*size] as wanted
    if (position < 0) {
        position += size;
    }

    // revert the boundaries to the original position
    position += lowerBound;

    return std::make_pair(position, velocity);
}

double PeriodicDimension::calculateShortestDistance(double pos1, double pos2)
                                                                        const {
    double distance = 0;
    
    if ( fabs(pos1 - (pos2 + size)) < fabs(pos1 - pos2) ) {
        // pos2 very close to boundary, distance shorter over the boundary
        distance = this->calculateDistance(pos1, pos2 + size);

    } else if ( fabs((pos1 + size) - pos2) < fabs(pos1 - pos2) ) {
        // pos1 very close to boundary, distance shorter over the boundary
        distance = this->calculateDistance(pos1 + size, pos2);

    } else {
        // shortest distance is between the particles as they are
        distance = this->calculateDistance(pos1, pos2);
    }

    return distance;
}

} // namespace PSO
