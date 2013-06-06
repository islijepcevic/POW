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

#include <cstdio>

namespace PSO {

Particle::Particle() {
}

Particle::Particle(const int _index, const int noDimensions) :
        index(_index),
        currentPosition(noDimensions),
        currentVelocity(noDimensions),
        currentValue(VERY_LARGE_VALUE),
        bestPosition(noDimensions),
        bestValue(VERY_LARGE_VALUE) {
}

Particle::Particle(const Particle& _particle) :
    index(_particle.index),
    currentPosition(_particle.currentPosition),
    currentVelocity(_particle.currentVelocity),
    currentValue(_particle.currentValue),
    bestPosition(_particle.bestPosition),
    bestValue(_particle.bestValue) {
}

Particle::~Particle() {
    printf("Particle destructor\n");
}

Particle& Particle::operator=(Particle _particle) {
    swap(*this, _particle);
    return *this;
}

//Particle& Particle::operator=(const Particle& _particle) {
//
//
//    index = _particle.index;
//    currentPosition.clear();
//    currentPosition = _particle.currentPosition;
//    currentVelocity = _particle.currentVelocity;
//    currentValue = _particle.currentValue;
//    bestPosition = _particle.bestPosition;
//    bestValue = _particle.bestValue;
//
//    return *this;
//}

int Particle::getIndex() {
    return index;
}

void Particle::seed(const PsoSpace& space) {
    currentValue = bestValue = VERY_LARGE_VALUE;

    for (int d = 0; d < currentPosition.size(); d++) {
        currentPosition[d] = bestPosition[d] = randDouble(
                space.getLowerBound(d), space.getHigherBound(d)
        );
        currentVelocity[d] = randDouble( -space.getSize(d), space.getSize(d) );
    }
}

std::ostream& operator<<(std::ostream& out, const Particle& part) {
    out << "PARTICLE " << part.index << std::endl;

    out << "pos: ";
    for (int i = 0; i < part.currentPosition.size(); i++) {
        out << part.currentPosition[i] << " ";
    }
    out << std::endl;

    out << "vel: ";
    for (int i = 0; i < part.currentVelocity.size(); i++) {
        out << part.currentVelocity[i] << " ";
    }
    out << std::endl;

    out << "value: " << part.currentValue << std::endl;


    out << "best pos: ";
    for (int i = 0; i < part.bestPosition.size(); i++) {
        out << part.bestPosition[i] << " ";
    }
    out << std::endl;

    out << "best value: " << part.bestValue << std::endl;

    out << std::endl;
}

void swap(Particle& p1, Particle& p2) {
    using std::swap; // maybe switch to boost::swap

    swap(p1.index, p2.index);
    swap(p1.currentPosition, p2.currentPosition);
    swap(p1.currentVelocity, p2.currentVelocity);
    swap(p1.currentValue, p2.currentValue);
    swap(p1.bestPosition, p2.bestPosition);
    swap(p1.bestValue, p2.bestValue);
}


} // namespace PSO 
