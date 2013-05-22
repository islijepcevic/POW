/*
 * AbstractSpace.cpp
 *
 * Abstract space for the use in c++ part of PSO
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "AbstractSpace.hpp"

namespace PSO {

//AbstractSpace::AbstractSpace(const std::vector<Dimension*>& _dimensions) :
//    dimensions(_dimensions) {
//
//}

AbstractSpace::~AbstractSpace() {
}

//int AbstractSpace::getNoDimensions() const {
//    return dimensions.size();
//}
//
//double AbstractSpace::getLowerBound(int dimensionIndex) {
//    return dimensions[dimensionIndex].getLowerBound();
//}
//
//double AbstractSpace::getHigherBound(int dimensionIndex) {
//    return dimensions[dimensionIndex].getHigherBound();
//}
//
//double AbstractSpace::getSize(int dimensionIndex) {
//    return dimensions[dimensionIndex].getSize();
//}
//
//void AbstractSpace::checkBoundaries(Particle& particle) const {
//    // TODO
//}
//
//void AbstractSpace::calculateDistanceVector(const Particle& particle1,
//                                        const Particle& particle2) const {
//    // TODO
//    //
//    // for every dimension, get the distance between two particles
//}
//
//void AbstractSpace::calculateShortestDistanceVector(const Particle& particle1,
//                                        const Particle& particle2) const {
//    // TODO
//    //
//    // for every dimension, get the shortest distance between two particles
//}

} // namespace PSO
