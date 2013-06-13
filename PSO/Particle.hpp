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
#include <iostream>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/packed_oarchive.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "PsoSpaceForward.hpp"

namespace PSO {

class Particle {
private:

    // index of the particle
    int index;

    // BOOST SERIALIZATION
    friend class boost::serialization::access;

    /*
     * method that for serializing and deserializing objects of this class
     * @param ar - archive stream
     * @param version - don't know, not used
     */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & index;
        //ar & const_cast<int&>(INDEX);
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
     * basic constructor. This is meant to be used only for the purpose of
     * skeleton-content pattern of Boost.MPI. Master process creates the
     * skeleton of the particle using different constructor, and sends it to
     * all the other processes.  Then, only the content of the particles is
     * passed, to reduce the number of copying the data while communicating
     * via MPI.
     */
    Particle();

    /*
     * constructor. This constructor is to be used by Master node when the
     * first particle is created.
     * @param noDimensions - number of dimensions
     */
    Particle(const int _index, const int noDimensions);

    /*
     * copy constructor
     */
    Particle(const Particle& _particle);

    /*
     * destructor
     */
    virtual ~Particle();

    /*
     * assignment operator
     */
    //Particle& operator=(const Particle& _particle);
    Particle& operator=(Particle _particle);

    /*
     * getter for particle index
     */
    int getIndex();

    /*
     * seeds a particle to the new random position
     * @param space - a reference to space
     */
    void seed(const PsoSpace& space);

    /*
     * overloaded << operator for printing the object
     */
    friend std::ostream& operator<<(std::ostream& out, const Particle& part);

    friend void swap(Particle& p1, Particle& p2);
};

} // namespace PSO 

#endif // __PARTICLE__
