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

namespace PSO {

class Dimension {
private:
    
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
    Dimension(const double _lower, const double _higher) :
        lowerBound(_lower), _higher(higherBound),
        size(higherBound - lowerBound) {

        if size < 0 {
            throw std::invalid_argument("dimension size is negative");
        }
    }

    /*
     * destructor
     */
    virtual ~Dimension() {}

    /*
     * method that checks boundaries for a specific boundary conditions
     * @param position - position of the particle in given dimension
     * @param velocity - velocity of the particle in the given dimension
     * @return - pair of new position and velocity
     */
    virtual std::pair<double, double>
        checkBoundaries(double position, double velocity) const = 0;
};

} // namspace PSO

#endif // __DIMENSION__
