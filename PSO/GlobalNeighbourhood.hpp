/*
 * GlobalNeighbourhood.hpp
 *
 * a class representing global neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __GLOBAL_NEIGHBOURHOOD__
#define __GLOBAL_NEIGHBOURHOOD__

#include "Neighbourhood.hpp"

namespace PSO {

class GlobalNeighbourhood : public Neighbourhood {
private:

    Particle& bestParticle;
    
public:

    GlobalNeighbourhood(const Swarm& _swarm);

    ~GlobalNeighbourhood();

    // Override
    virtual void scanNeighbours();

    // Override
    virtual Particle& findBestNeighbour(int particleIndex) const; 
};

} // namespace PSO

#endif // __GLOBAL_NEIGHBOURHOOD__
