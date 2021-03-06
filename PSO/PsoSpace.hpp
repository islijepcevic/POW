/*
 * PsoSpace.hpp
 *
 * Abstract space for the use in c++ part of PSO
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __PSO_SPACE__
#define __PSO_SPACE__

#include <vector>
//#include <boost/mpi/packed_iarchive.hpp>
//#include <boost/mpi/packed_oarchive.hpp>
//#include <boost/serialization/vector.hpp>

#include "Dimension.hpp"
#include "Particle.hpp"

namespace PSO {

class PsoSpace {
private:

    // this is for the description of dimensions
    std::vector<Dimension*> dimensions;

    int noDimensions;

//    // BOOST SERIALIZATION
//    friend class boost::serialization::access;
//
//    /**
//     * method that for serializing and deserializing objects of this class
//     * @param ar - archive stream
//     * @param version - don't know, not used
//     */
//    template<class Archive>
//    void serialize(Archive& ar, const unsigned int version) {
//        ar & dimensions;
//        ar & noDimensions;
//    }

public:

    /**
     * default constructor - for slave processes
     */
    PsoSpace();

    /**
     * constructor
     * empty implementation provided
     */
    PsoSpace(const std::vector<Dimension*>& _dimensions);

    /**
     * copy costructor
     */
    PsoSpace(const PsoSpace& _space);

    /**
     * destructor
     * empty imelpmentation provided
     */
    virtual ~PsoSpace();

    /**
     * assignment operator
     */
    PsoSpace& operator= (const PsoSpace& _space);


    /**
     * getter for number of dimensions
     * @return - number of dimensions
     */
    int getNoDimensions() const;

    /**
     * getter for lower bound of wanted dimension
     * @param dimensionIndex - index of the wanted dimension
     * @return - lower bound for given dimension
     */
    double getLowerBound(int dimensionIndex) const;

    /**
     * getter for higher bound of wanted dimension
     * @param dimensionIndex - index of the wanted dimension
     * @return - higher bound for given dimension
     */
    double getHigherBound(int dimensionIndex) const;

    /**
     * getter for lower bound of dimension d
     * @param dimensionIndex - index of the wanted dimension
     * @return - lower bound for given dimension
     */
    double getSize(int dimensionIndex) const;

    /**
     * method that checks particle's position if it is within boundaries of this
     * space. If not, then position and velocity are updated, for each dimension
     * in the specific way
     * @param particle - particle whose position is checked and updated
     */
    void checkBoundaries(Particle& particle) const;

    /**
     * returns distance vector between two positions in this space.
     * Distance is calculated from first position to second position, equivalent
     * to pos2 - pos1
     * @param pos1 - first position
     * @param pos2 - second position
     * @return - distance vector
     */
    std::vector<double> calculateDistanceVector(
        const std::vector<double>& pos1, const std::vector<double>& pos2) const;

    /**
     * returns shortest distance between two positions in this space
     * in dimensions of some type, distance can be measured in several ways,
     * and this method guarantees to return the shortest possible distance.
     * Distance is calculated from first position to second position, equivalent
     * to pos2 - pos1 (while taking dimension type into account)
     * @param pos1 - first position
     * @param pos2 - second position
     * @return - shortest distance vector
     */
    std::vector<double> calculateShortestDistanceVector(
        const std::vector<double>& pos1, const std::vector<double>& pos2) const;

};

} // namespace PSO

#endif // __PSO_SPACE__
