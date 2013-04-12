/*
 * AbstractFitness.hpp
 *
 * Abstract fitness function for the use in c++ part of PSO
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __ABSTRACT_FITNESS__
#define __ABSTRACT_FITNESS__

namespace PSO {

class AbstractFitness {
public:

    /*
     * constructor
     * empty implementation provided
     */
    AbstractFitness() {}

    /*
     * destructor
     * empty imelpmentation provided
     */
    virtual ~AbstractFitness() {}

    /*
     * a method to use in c++ for calling the evaluation
     * it is intended that derived class in Python implements this method by
     * calling another evaluate method that will be implemented by the end user
     * of POW
     *
     * @param particle - a particle whose position is about to get evaluated
     * @return         - the value of the particle for this fitness function
     */
    virtual double evaluation(const Particle& particle) = 0;
};

}

#endif // __ABSTRACT_FITNESS__
