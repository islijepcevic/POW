/*
 * EmptyRepulsionField.cpp
 *
 * a class that is used for repulsion field when no repulsion is to be used
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "EmptyRepulsionField.hpp"

namespace PSO {

EmptyRepulsionField::EmptyRepulsionField() {
}

EmptyRepulsionField::~EmptyRepulsionField() {
}

void EmptyRepulsionField::addRepeller(const std::vector<double>& position) {
}

void EmptyRepulsionField::apply(Particle& particle, const PsoSpace& space) const
{
}

} // namespace PSO

BOOST_CLASS_EXPORT_IMPLEMENT(PSO::EmptyRepulsionField);
