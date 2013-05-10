/*
 * Particle.hpp
 *
 * a class that represents one particle of PSO
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __PARTICLE__
#define __PARTICLE__

#include <vector>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#define VERY_LARGE_VALUE 100000000

namespace PSO {

class Particle {
private:
    // BOOST SERIALIZATION
    friend class boost::serialization::access;

    /*
     * method that for serializing and deserializing objects of this class
     * @param ar - archive stream
     * @param version - don't know, not used
     */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & currentPosition;
        ar & currentVelocity;
        ar & currentValue;
        ar & bestPosition;
        ar & bestValue;
    }

public:

    // variables associated to current solution
    std::vector<double> currentPosition;
    std::vector<double> currentVelocity;
    double currentValue;

    // variables associated to best possible solution
    std::vector<double> bestPosition;
    double bestValue;

// methods

    /*
     * constructor
     * @param noDimensions - number of dimensions
     */
    Particle(int noDimensions);

    /*
     * destructor
     */
    ~Particle();

    /*
     * seeds a particle to the new random position
     * @param space - a reference to space
     */
    void seed(const AbstractSpace& space);
};

} // namespace PSO 

#endif // __PARTICLE__
