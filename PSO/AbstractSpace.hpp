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
#include "Dimension.h"

namespace PSO {

class AbstractSpace {
private:

    // this is for the description of dimensions
    const std::vector<Dimension*>& dimensions;

public:

    /*
     * constructor
     * empty implementation provided
     */
    AbstractSpace(const std::vector<Dimension*>& _dimensions);

    /*
     * destructor
     * empty imelpmentation provided
     */
    virtual ~AbstractSpace();

    /*
     *
     */
    virtual void checkBoundaries(Particle& particle) const;

};

} // namespace PSO

#endif // __ABSTRACT_SPACE__
