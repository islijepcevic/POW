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

    // revert the boundaries to the original position
    position += lowerBound;

    return std::make_pair(position, velocity);
}

} // namespace PSO
