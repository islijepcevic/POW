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
#include "Dimension.hpp"
#include "Particle.hpp"

namespace PSO {

class PsoSpace {
private:

    // this is for the description of dimensions
    std::vector<Dimension*> dimensions;

    int noDimensions;

public:

    /*
     * default constructor - for slave processes
     */
    PsoSpace();

    /*
     * constructor
     * empty implementation provided
     */
    PsoSpace(const std::vector<Dimension*>& _dimensions);

    /*
     * copy costructor
     */
    PsoSpace(const PsoSpace& _space);

    /*
     * destructor
     * empty imelpmentation provided
     */
    virtual ~PsoSpace();

    /*
     * assignment operator
     */
    PsoSpace& operator= (const PsoSpace& _space);


    /*
     * getter for number of dimensions
     * @return - number of dimensions
     */
    int getNoDimensions() const;

    /*
     * getter for lower bound of wanted dimension
     * @param dimensionIndex - index of the wanted dimension
     * @return - lower bound for given dimension
     */
    double getLowerBound(int dimensionIndex);

    /*
     * getter for higher bound of wanted dimension
     * @param dimensionIndex - index of the wanted dimension
     * @return - higher bound for given dimension
     */
    double getHigherBound(int dimensionIndex);

    /*
     * getter for lower bound of dimension d
     * @param dimensionIndex - index of the wanted dimension
     * @return - lower bound for given dimension
     */
    double getSize(int dimensionIndex);

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

#endif // __PSO_SPACE__
