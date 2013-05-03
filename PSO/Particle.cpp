/*
 * Particle.cpp
 *
 * a class that represents one particle of PSO
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "Particle.hpp"

#include "constants.hpp"

namespace PSO {

Particle::Particle(int noDimensions) :
        currentPosition(noDimensions),
        currentVelocity(noDimensions),
        currentValue(VERY_LARGE_VALUE),
        bestPosition(noDimensions),
        bestValue(VERY_LARGE_VALUE) {
}

Particle::~Particle() {
}

void Particle::seed(const AbstractSpace& space) {
    currentValue = bestValue = VERY_LARGE_VALUE;

    for (int d = 0; d < currentPosition.size(); d++) {
        currentPosition[d] = bestPosition[d] = randDouble(
                space.getLowerBound(d), space.getHigherBound(d)
        );
        currentVelocity[d] = randDouble( -space.getSize(d), space.getSize(d) );
    }
}

} // namespace PSO 
