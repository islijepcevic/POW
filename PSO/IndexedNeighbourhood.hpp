/*
 * IndexedNeighbourhood.hpp
 *
 * a class representing indexed local neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __INDEXED_NEIGHBOURHOOD__
#define __INDEXED_NEIGHBOURHOOD__

#include "Neighbourhood.hpp"

namespace PSO {

class IndexedNeighbourhood : public Neighbourhood {
private:

    // TODO
public:

    IndexedNeighbourhood(const Swarm& _swarm);

    ~IndexedNeighbourhood();

    // Override
    virtual void scanNeighbours();

    // Override
    virtual Particle& findBestNeighbour(int particleIndex) const; 
};

} // namespace PSO

#endif // __INDEXED_NEIGHBOURHOOD__
