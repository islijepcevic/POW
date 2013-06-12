/*
 * FitnessProxy.hpp
 *
 * A proxy class to Fitness class in python
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __ABSTRACT_FITNESS_PROXY__
#define __ABSTRACT_FITNESS_PROXY__

#include "Particle.hpp"

namespace PSO {

class AbstractFitnessProxy {
public:

    /*
     * constructor
     * empty implementation provided
     */
    AbstractFitnessProxy() {}

    /*
     * destructor
     * empty imelpmentation provided
     */
    virtual ~AbstractFitnessProxy() {}

    /*
     * a method to use in c++ for calling the evaluation
     * it is intended that derived class in Python implements this method 
     * that class will have a reference to user's Fitness class
     *
     * @param particle - a particle whose position is about to get evaluated
     * @return         - the value of the particle for this fitness function
     */
    virtual double evaluation(const Particle& particle) = 0;
};

} // namespace PSO

#endif // __ABSTRACT_FITNESS_PROXY__
