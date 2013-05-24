/*
 * PsoSpace.cpp
 *
 * space class for the use in c++ part of PSO
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PsoSpace.hpp"

namespace PSO {

PsoSpace::PsoSpace() {
}

PsoSpace::PsoSpace(const std::vector<Dimension*>& _dimensions) :
    dimensions(_dimensions) {

}

PsoSpace::~PsoSpace() {
    for (int i = 0; i < dimensions.size(); i++) {
        delete dimensions[i];
    }
}

int PsoSpace::getNoDimensions() const {
    return dimensions.size();
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

//void PsoSpace::checkBoundaries(Particle& particle) const {
//    // TODO
//}
//
//void PsoSpace::calculateDistanceVector(const Particle& particle1,
//                                        const Particle& particle2) const {
//    // TODO
//    //
//    // for every dimension, get the distance between two particles
//}
//
//void PsoSpace::calculateShortestDistanceVector(const Particle& particle1,
//                                        const Particle& particle2) const {
//    // TODO
//    //
//    // for every dimension, get the shortest distance between two particles
//}

} // namespace PSO
