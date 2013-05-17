/*
 * AbstractSpace.hpp
 *
 * Abstract space for the use in c++ part of PSO
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __ABSTRACT_SPACE__
#define __ABSTRACT_SPACE__

#include <vector>
//#include "Dimension.hpp"

namespace PSO {

class AbstractSpace {
private:

//    // this is for the description of dimensions
//    const std::vector<Dimension*>& dimensions;

public:

    /*
     * THIS CONSTRUCTOR IS JUST FOR THE DUMMY ABSTRACT SPACE, FOR TESTING AND
     * DEVELOPING PURPOSES
     * WITH THIS CONSTRUCTOR, THE MAJORITY OF THE IMPLEMENTATION IS STILL IN THE
     * PYTHON CODE
     *
     * DELETE THIS CONSTRUCTOR WHEN THE OTHER ONE COMES IN ACTION
     */
    AbstractSpace() {}

//    /*
//     * constructor
//     * empty implementation provided
//     */
//    AbstractSpace(const std::vector<Dimension*>& _dimensions);

    /*
     * destructor
     * empty imelpmentation provided
     */
    virtual ~AbstractSpace();

//    /*
//     * getter for number of dimensions
//     * @return - number of dimensions
//     */
//    int getNoDimensions() const;
//
//    /*
//     * getter for lower bound of wanted dimension
//     * @param dimensionIndex - index of the wanted dimension
//     * @return - lower bound for given dimension
//     */
//    double getLowerBound(int dimensionIndex);
//
//    /*
//     * getter for higher bound of wanted dimension
//     * @param dimensionIndex - index of the wanted dimension
//     * @return - higher bound for given dimension
//     */
//    double getHigherBound(int dimensionIndex);
//
//    /*
//     * getter for lower bound of dimension d
//     * @param dimensionIndex - index of the wanted dimension
//     * @return - lower bound for given dimension
//     */
//    double getSize(int dimensionIndex);
//
//    /*
//     *
//     */
//    void checkBoundaries(Particle& particle) const;
//
//    /*
//     * do not return void
//     */
//    void calculateDistanceVector(const Particle& particle1,
//                            const Particle& particle2) const;
//
//    /*
//     * do not return void
//     */
//    void calculateShortestDistanceVector(const Particle& particle1,
//                            const Particle& particle2) const;

};

} // namespace PSO

#endif // __ABSTRACT_SPACE__
