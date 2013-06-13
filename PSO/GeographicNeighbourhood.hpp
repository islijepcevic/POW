/*
 * GeographicNeighbourhood.hpp
 *
 * a class representing geometric local neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __GEOGRAPHIC_NEIGHBOURHOOD__
#define __GEOGRAPHIC_NEIGHBOURHOOD__

#include "Neighbourhood.hpp"

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>

namespace PSO {

/**
 * GeographicNeighbourhood is a type of neighbourhood where particles are
 * influenced by nearest ones in the search place at a given moment.
 */
class GeographicNeighbourhood : public Neighbourhood {
private:

    /**
     * for every particle, store the best particle in the neighbourhood
     */
    std::vector<Particle> bestNeighbours;

    /**
     * this number represents the total size of neighbourhood
     * this means that the nearest nhoodSize particles will be considered (not
     * counting the particle itself)
     */
    int nhoodSize;

    // BOOST SERIALIZATION
    friend class boost::serialization::access;

    /*
     * method that for serializing and deserializing objects of this class
     * @param ar - archive stream
     * @param version - don't know, not used
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Neighbourhood>(*this);
        ar & bestNeighbours;
        ar & nhoodSize;
    }

public:

    GeographicNeighbourhood();

    GeographicNeighbourhood(int nParticles, int _nhoodSize);

    virtual ~GeographicNeighbourhood();

    /// Override
    virtual void scanNeighbours(const Swarm& swarm);

    /// Override
    virtual const Particle& findBestNeighbour(int particleIndex) const; 
};

} // namespace PSO

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_KEY(PSO::GeographicNeighbourhood);

#endif // __GEOGRAPHIC_NEIGHBOURHOOD__
