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

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>

namespace PSO {

/**
 * Indexed neighbourhood is a type of neighbourhood in which all particles are
 * stored in a list/array, and then the neighbours in this list, with respect to
 * the index to the array, are considered.
 */
class IndexedNeighbourhood : public Neighbourhood {
private:

    /**
     * for every particle, store the best particle in the neighbourhood
     */
    std::vector<Particle> bestNeighbours;

    /**
     * this number represents the size of neighbourhood in one direction
     * that means, the total neighbourhood size will be:
     * SIZE = 2*nhoodSize + 1
     * because it will count for nhoodSize to the left, then nhoodSize to the
     * right and finally, the particle itself;
     * particles are assumed to be in circular order, so that particle 0 will
     * have neighbours 1 and the last one.
     */
    int nhoodSize;

    // boost serialization
    friend class boost::serialization::access;

    /*
     * method that for serializing and deserializing objects of this class
     * @param ar - archive stream
     * @param version - don't know, not used
     */
    template<class archive>
    void serialize(archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Neighbourhood>(*this);
        ar & bestNeighbours;
        ar & nhoodSize;
    }

public:

    IndexedNeighbourhood();

    IndexedNeighbourhood(int nParticles, int _nhoodSize);

    ~IndexedNeighbourhood();

    // Override
    virtual void scanNeighbours(const Swarm& swarm);

    // Override
    virtual const Particle& findBestNeighbour(int particleIndex) const; 
};

} // namespace PSO

#endif // __INDEXED_NEIGHBOURHOOD__
