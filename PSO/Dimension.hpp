/*
 * Dimension.hpp
 *
 * Class that represents one dimension, with its lower and higher boundaries
 * and the cell size. Subclasses of this class should implement various
 * boundary checking
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __DIMENSION__
#define __DIMENSION__

#include <utility>
#include <stdexcept>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
//#include <boost/serialization/serialization.hpp>
//#include <boost/serialization/nvp.hpp>

namespace PSO {

class Dimension {
private:
//    // BOOST SERIALIZATION
//    friend class boost::serialization::access;
//
//    /*
//     * method that for serializing and deserializing objects of this class
//     * @param ar - archive stream
//     * @param version - don't know, not used
//     */
//    template<class Archive>
//    void serialize(Archive& ar, const unsigned int version) {
//        ar & boost::serialization::make_nvp("LowerBound", lowerBound);
//        ar & boost::serialization::make_nvp("HigherBound", higherBound);
//        ar & boost::serialization::make_nvp("Size", size);
//    }

protected:
    
    // lower bound of the dimension
    double lowerBound;

    // higher bound of the dimension
    double higherBound;

    // size of the dimension
    double size;

public:

    /*
     * constructor
     */
    Dimension(const double _lower, const double _higher);

    /*
     * destructor
     */
    virtual ~Dimension();

    /*
     * getter for lower bound
     * @return - lower bound
     */
    double getLowerBound();

    /*
     * getter for higher bound
     * @return - higher bound
     */
    double getHigherBound();

    /*
     * getter for dimension size
     * @return - size of this dimension
     */
    double getSize();

    /*
     * method that checks boundaries for a specific boundary conditions
     * @param position - position of the particle in given dimension
     * @param velocity - velocity of the particle in the given dimension
     * @return - pair of new position and velocity
     */
    virtual std::pair<double, double>
        checkBoundaries(double position, double velocity) const = 0;

    /*
     * calculates distance between two points in this dimension
     * assumes that both positions are within the dimension size
     * @param pos1 - first position
     * @param pos2 - second position
     * @return - distance
     */
    virtual double calculateDistance(double pos1, double pos2) const;

    /*
     * calculates shortest distance between two points in this dimension
     * assumes that both positions are within the dimension size
     * @param pos1 - first position
     * @param pos2 - second position
     * @return - shortest distance
     */
    virtual double calculateShortestDistance(double pos1, double pos2)
                                                                const = 0;
};

//BOOST_SERIALIZATION_ASSUME_ABSTRACT(Dimension);

} // namspace PSO

#endif // __DIMENSION__
