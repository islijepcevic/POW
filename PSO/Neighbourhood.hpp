/**
 * Neighbourhood.hpp
 *
 * an abstract class for representing particle neighbourhoood types
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __NEIGHBOURHOOD__
#define __NEIGHBOURHOOD__

#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/packed_oarchive.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
//#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp>

#include "SwarmForward.hpp"
#include "Particle.hpp"

namespace PSO {

class Neighbourhood {
private:
    // BOOST SERIALIZATION
    friend class boost::serialization::access;

    /**
     * method that for serializing and deserializing objects of this class
     * @param ar - archive stream
     * @param version - don't know, not used
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
    }

public:

    Neighbourhood() {
    }

    virtual ~Neighbourhood() {
    }

    /**
     * scans all the necessary positions in the swarm, such that finding the
     * best neighbour can be fast
     */
    virtual void scanNeighbours(const Swarm& swarm) = 0;

    /**
     * finding the best evaluated neighbour for the given particle
     * @param particleIndex - index of a given particle in the swarm
     * @return - index of the best evaluated particle in the neighbourhood
     */
    virtual const Particle& findBestNeighbour(int particleIndex) const = 0;
};

} // namespace PSO

BOOST_SERIALIZATION_ASSUME_ABSTRACT(PSO::Neighbourhood);
//BOOST_CLASS_EXPORT_KEY(PSO::Neighbourhood);

#endif // __NEIGHBOURHOOD__
