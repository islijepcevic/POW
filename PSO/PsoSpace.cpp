/*
 * PsoSpace.cpp
 *
 * space class for the use in c++ part of PSO
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PsoSpace.hpp"

#include <cstdio>

namespace PSO {

PsoSpace::PsoSpace() {
}

PsoSpace::PsoSpace(const std::vector<Dimension*>& _dimensions) :
    dimensions(_dimensions),
    noDimensions(dimensions.size()) {
}

PsoSpace::PsoSpace(const PsoSpace& _space) :
    dimensions(_space.dimensions),
    noDimensions(_space.noDimensions) {
}

PsoSpace::~PsoSpace() {
    for (int i = 0; i < dimensions.size(); i++) {
        delete dimensions[i];
    }
}

PsoSpace& PsoSpace::operator= (const PsoSpace& _space) {
    dimensions = _space.dimensions;
    return *this;
}

int PsoSpace::getNoDimensions() const {
    return noDimensions;
}

double PsoSpace::getLowerBound(int dimensionIndex) {
    return dimensions[dimensionIndex]->getLowerBound();
}

double PsoSpace::getHigherBound(int dimensionIndex) {
    return dimensions[dimensionIndex]->getHigherBound();
}

double PsoSpace::getSize(int dimensionIndex) {
    return dimensions[dimensionIndex]->getSize();
}

void PsoSpace::checkBoundaries(Particle& particle) const {

    for (int i = 0; i < noDimensions; i++) {
        std::pair<double, double> pv = dimensions[i]->checkBoundaries(
                particle.currentPosition[i], particle.currentVelocity[i]
        );

        particle.currentPosition[i] = pv.first;
        particle.currentVelocity[i] = pv.second;
    }
}

std::vector<double> PsoSpace::calculateDistanceVector(const Particle& particle1,
                                        const Particle& particle2) const {

    // for every dimension, get the distance between two particles
    std::vector<double> dist;
    dist.reserve( getNoDimensions() );

    for (int i = 0; i < noDimensions; i++) {
        double p1 = particle1.currentPosition[i];
        double p2 = particle2.currentPosition[i];
        dist.push_back( dimensions[i]->calculateDistance(p1, p2) );
    }

    return dist;
}

std::vector<double> PsoSpace::calculateShortestDistanceVector(
                const Particle& particle1, const Particle& particle2) const {

    // for every dimension, get the shortest distance between two particles
    std::vector<double> dist;
    dist.reserve( getNoDimensions() );

    for (int i = 0; i < noDimensions; i++) {
        double p1 = particle1.currentPosition[i];
        double p2 = particle2.currentPosition[i];
        dist.push_back( dimensions[i]->calculateShortestDistance(p1, p2) );
    }

    return dist;
}

} // namespace PSO
