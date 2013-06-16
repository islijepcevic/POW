/*
 * PotentialRepulsionField.cpp
 *
 * a class that is used for repulsion field with simple potential repulsion
 * factor
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PotentialRepulsionField.hpp"

#include <cmath>

namespace PSO {

PotentialRepulsionField::PotentialRepulsionField() {
}

PotentialRepulsionField::PotentialRepulsionField(double _repulsionFactor) :
    RepulsionField(_repulsionFactor) {
}

PotentialRepulsionField::~PotentialRepulsionField() {
}

void PotentialRepulsionField::addRepeller(const std::vector<double>& position) {
    repellers.push_back(position);
}

void PotentialRepulsionField::apply(Particle& particle, const PsoSpace& space)
        const {
    
    std::vector<double> bias(space.getNoDimensions(), 0.0);

    for (unsigned int r = 0; r < repellers.size(); r++) {
        std::vector<double> distance = space.calculateShortestDistanceVector(
            particle.currentPosition, repellers[r]
        );
        for (int d = 0; d < space.getNoDimensions(); d++) {
            double repScale = space.getSize(d) * repulsionFactor;
            if (distance[d] < repScale) {
                bias[d] -= repScale / distance[d] / distance[d];
            }
        }
    }

    for (int d = 0; d < space.getNoDimensions(); d++) {
        if (fabs(bias[d]) > space.getSize(d)) {
            bias[d] = copysign(space.getSize(d), bias[d]);
        }

        particle.currentPosition[d] += bias[d];
        particle.currentVelocity[d] += bias[d];
    }

    space.checkBoundaries(particle);
}

} // namespace PSO

BOOST_CLASS_EXPORT_IMPLEMENT(PSO::PotentialRepulsionField);
