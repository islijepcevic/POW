#include "ReflexiveDimension.hpp"

#include <cmath>

ReflexiveDimension::ReflexiveDimension(const double _lower,
                                    const double _higher) :
    Dimension(_lower, _higher) {
}

ReflexiveDimension::~ReflexiveDimension() {
}

std::pair<double, double> ReflexiveDimension::checkBoundaries(double position,
                                                        double velocity) const {

    // scale boundaries interval such that lower bound starts from zero
    position -= lowerBound;
    
    // apply the boundary conditions
    
    // dimension is now 2*size periodic; so first get the position to the
    // interval [0, 2*size]
    position = fmod(position, 2.0 * size);

    if (position > size) {
        // this is equivalent to: size - (position - size)
        position = 2 * size - position;

        // this is the case when there is odd number of "bounces from the wall"
        // so the velocity shoud be in opposite direction
        velocity *= -1.0;
    }

    // revert the interval to the original position
    position += lowerBound;

    return std::make_pair(position, velocity);
}

