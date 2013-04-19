#include "AbstractSpace.hpp"

namespace PSO {

AbstractSpace::AbstractSpace(const std::vector<Dimension*>& _dimensions) :
    dimensions(_dimensions) {

}

AbstractSpace::~AbstractSpace() {
}

void AbstractSpace::checkBoundaries(Particle& particle) const {
    // TODO
}


} // namespace PSO
