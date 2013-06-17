/*
 * Dimension.cpp
 *
 * Class that represents one dimension, with its lower and higher boundaries
 * and the cell size. Subclasses of this class should implement various
 * boundary checking
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "Dimension.hpp"

namespace PSO {

Dimension::Dimension(const double _lower, const double _higher) :
    lowerBound(_lower), higherBound(_higher),
    size(higherBound - lowerBound) {

    if (size < 0) {
        throw std::invalid_argument("dimension size is negative");
    }
}

Dimension::~Dimension() {
}

double Dimension::getLowerBound() {
    return lowerBound;
}

double Dimension::getHigherBound() {
    return higherBound;
}

double Dimension::getSize() {
    return size;
}

double Dimension::calculateDistance(double pos1, double pos2) const {
    return pos2 - pos1;
}

} // namespace PSO

