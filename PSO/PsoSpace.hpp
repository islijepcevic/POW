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
    double getLowerBound(int dimensionIndex) const;

    /*
     * getter for higher bound of wanted dimension
     * @param dimensionIndex - index of the wanted dimension
     * @return - higher bound for given dimension
     */
    double getHigherBound(int dimensionIndex) const;

    /*
     * getter for lower bound of dimension d
     * @param dimensionIndex - index of the wanted dimension
     * @return - lower bound for given dimension
     */
    double getSize(int dimensionIndex) const;

    /*
     * method that checks particle's position if it is within boundaries of this
     * space. If not, then position and velocity are updated, for each dimension
     * in the specific way
     * @param particle - particle whose position is checked and updated
     */
    void checkBoundaries(Particle& particle) const;

    /*
     * returns distance between two particles in this space
     * @param particle1 - first particle
     * @param particle2 - second particle
     * @return - distance vector
     */
    std::vector<double> calculateDistanceVector(const Particle& particle1,
                            const Particle& particle2) const;

    /*
     * returns shortest distance between two particles in this space
     * in dimensions of some type, distance can be measured in several ways,
     * and this method surely returns the shortest possible distance
     * @param particle1 - first particle
     * @param particle2 - second particle
     * @return - shortest distance vector
     */
    std::vector<double> calculateShortestDistanceVector(
            const Particle& particle1, const Particle& particle2) const;

};

} // namespace PSO

#endif // __PSO_SPACE__
