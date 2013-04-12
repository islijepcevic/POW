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

namespace PSO {

class AbstractSpace {
public:

    /*
     * constructor
     * empty implementation provided
     */
    AbstractSpace() {}

    /*
     * destructor
     * empty imelpmentation provided
     */
    virtual ~AbstractSpace() {}

};

}

#endif // __ABSTRACT_SPACE__
