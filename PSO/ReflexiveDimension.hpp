/*
 * ReflexiveDimension.hpp
 *
 * Subclass of Dimension with reflexive boundary condition
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __REFLEXIVE_DIMENSION__
#define __REFLEXIVE_DIMENSION__

#include <utility>
#include <stdexcept>

#include "Dimension.hpp"

namespace PSO {

class ReflexiveDimension : public Dimension {
public:

    /*
     * constructor
     */
    ReflexiveDimension(const double _lower, const double _higher);

    /*
     * destructor
     */
    virtual ~ReflexiveDimension() {}

    // Override
    virtual std::pair<double, double>
        checkBoundaries(double position, double velocity) const;
};

} // namespace PSO

#endif // __REFLEXIVE_DIMENSION__
