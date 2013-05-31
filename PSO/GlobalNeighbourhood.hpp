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

    /**
     * globally best found particle
     */
    Particle bestParticle;

public:

    GlobalNeighbourhood();

    ~GlobalNeighbourhood();

    // Override
    virtual void scanNeighbours(const Smarm& swarm);

    // Override
    virtual const Particle& findBestNeighbour(int particleIndex) const;
};

} // namespace PSO

#endif // __GLOBAL_NEIGHBOURHOOD__
