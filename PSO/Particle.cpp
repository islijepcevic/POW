/*
 * Particle.cpp
 *
 * a class that represents one particle of PSO
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "Particle.hpp"

#include "PsoSpace.hpp"
#include "constants.hpp"
#include "randomUtils.hpp"
#include <algorithm>
#include <cmath>

namespace PSO {

Particle::Particle() {
}

Particle::Particle(const int _index, const int noDimensions) :
        index(_index),
        oldPosition(noDimensions),
        currentPosition(noDimensions),
        currentVelocity(noDimensions),
        currentValue(VERY_LARGE_VALUE),
        bestPosition(noDimensions),
        bestValue(VERY_LARGE_VALUE) {
}

Particle::Particle(const Particle& _particle) :
    index(_particle.index),
    oldPosition(_particle.oldPosition),
    currentPosition(_particle.currentPosition),
    currentVelocity(_particle.currentVelocity),
    currentValue(_particle.currentValue),
    bestPosition(_particle.bestPosition),
    bestValue(_particle.bestValue) {
}

Particle::~Particle() {
}

Particle& Particle::operator=(Particle _particle) {
    swap(*this, _particle);
    return *this;
}

int Particle::getIndex() {
    return index;
}

bool Particle::getRepelFlag() const {
    return repelFlag;
}

void Particle::clearRepelFlag() {
    repelFlag = false;
}

double Particle::getVelocityValue() {
    double sum = 0.0;
    for (unsigned int i = 0; i < currentVelocity.size(); i++) {
        sum += currentVelocity[i] * currentVelocity[i];
    }
    return sqrt(sum);
}

void Particle::move() {
    for (unsigned int i = 0; i < currentPosition.size(); i++) {
        currentPosition[i] += currentVelocity[i];
    }
}

void Particle::seed(const PsoSpace& space) {
    kick(space);
    reseed(space);

    bestValue = VERY_LARGE_VALUE;
    repelFlag = false;
}

void Particle::kick(const PsoSpace& space) {

    repelFlag = true;

    for (unsigned int d = 0; d < currentPosition.size(); d++) {
        currentVelocity[d] = randDouble( -space.getSize(d), space.getSize(d) );
    }
}

void Particle::reseed(const PsoSpace& space) {
    currentValue = VERY_LARGE_VALUE;

    for (unsigned int d = 0; d < currentPosition.size(); d++) {
        currentPosition[d] = bestPosition[d] = randDouble(
                space.getLowerBound(d), space.getHigherBound(d)
        );
    }
}

std::ostream& operator<<(std::ostream& out, const Particle& part) {
    out << "PARTICLE " << part.index << std::endl;

    out << "pos: ";
    for (unsigned int i = 0; i < part.currentPosition.size(); i++) {
        out << part.currentPosition[i] << " ";
    }
    out << std::endl;

    out << "vel: ";
    for (unsigned int i = 0; i < part.currentVelocity.size(); i++) {
        out << part.currentVelocity[i] << " ";
    }
    out << std::endl;

    out << "value: " << part.currentValue << std::endl;


    out << "best pos: ";
    for (unsigned int i = 0; i < part.bestPosition.size(); i++) {
        out << part.bestPosition[i] << " ";
    }
    out << std::endl;

    out << "best value: " << part.bestValue << std::endl;

    out << std::endl;

    return out;
}

void swap(Particle& p1, Particle& p2) {
    using std::swap; // maybe switch to boost::swap

    swap(p1.index, p2.index);
    swap(p1.oldPosition, p2.oldPosition);
    swap(p1.currentPosition, p2.currentPosition);
    swap(p1.currentVelocity, p2.currentVelocity);
    swap(p1.currentValue, p2.currentValue);
    swap(p1.bestPosition, p2.bestPosition);
    swap(p1.bestValue, p2.bestValue);
}


} // namespace PSO 
