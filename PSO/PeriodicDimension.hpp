/*
 * PeriodicDimension.hpp
 *
 * Subclass of Dimension with periodic boundary condition
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __PERIODIC_DIMENSION__
#define __PERIODIC_DIMENSION__

#include <utility>
#include <stdexcept>

#include "Dimension.hpp"

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
    virtual ~PeriodicDimension();

    // Override
    virtual std::pair<double, double>
        checkBoundaries(double position, double velocity) const;
};

} // namespace PSO

#endif // __PERIODIC_DIMENSION__
