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
#ifndef __PERIODIC_DIMENSION__
#define __PERIODIC_DIMENSION__

#include <utility>
#include <stdexcept>

namespace PSO {

class PeriodicDimension : public Dimension {
public:

    /*
     * constructor
     */
    PeriodicDimension(const double _lower, const double _higher);

    /*
     * destructor
     */
    virtual ~PeriodicDimension() {}

    // Override
    virtual std::pair<double, double>
        checkBoundaries(double position, double velocity) const;
};

} // namespace PSO

#endif // __PERIODIC_DIMENSION__
