/*
 * GeometricNeighbourhood.hpp
 *
 * a class representing geometric local neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __GEOMETRIC_NEIGHBOURHOOD__
#define __GEOMETRIC_NEIGHBOURHOOD__

#include "Neighbourhood.hpp"

namespace PSO {

class GeometricNeighbourhood : public Neighbourhood {
private:

    // TODO
public:

    GeometricNeighbourhood(const Swarm& _swarm);

    ~GeometricNeighbourhood();

    // Override
    virtual void scanNeighbours();

    // Override
    virtual Particle& findBestNeighbour(int particleIndex) const; 
};

} // namespace PSO

#endif // __GEOMETRIC_NEIGHBOURHOOD__
