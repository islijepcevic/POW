/**
 * Swarm.hpp
 *
 * a class that contains the whole swarm of particles
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __SWARM__
#define __SWARM__

#include <vector>
#include <string>

#include "Particle.hpp"
#include "PsoSpace.hpp"

namespace PSO {

/**
 * a collection of all the paticles
 */
class Swarm {
protected:

    // array of all particles
    std::vector<Particle> particles;

    // reference to space
    PsoSpace& space;

public:

    /**
     * default constructor of the Swarm
     */
    Swarm();

    /**
     * constructor of the Swarm
     * (meant to be used in master process)
     */
    Swarm(int noParticles, PsoSpace& _space);

    /**
     * copy constructor
     */
    Swarm(const Swarm& _swarm);

    /**
     * destructor of the Swarm
     */
    ~Swarm();

    /**
     * assignment operator
     */
    Swarm& operator=(const Swarm& _swarm);

    /**
     * getter for the number of particles
     * @return - number of particles
     */
    int getNoParticles() const;

    /**
     * getter for the space
     * @return - reference to the space object
     */
    const PsoSpace& getSpace() const;

    /**
     * getter for a particular particle
     * @param index - index of the particle
     * @return - reference to the index-th particle
     */
    Particle& getParticle(int index);

    /**
     * getter for a particular particle
     * @param index - index of the particle
     * @return - reference to the index-th particle
     */
    const Particle& getParticle(int index) const;

    /**
     * setter for a particular particle; particle is copied in the array on the
     * position of its own index
     * @param particle - the particle to set
     */
    void setParticle(Particle& particle);

    /**
     * method that seeds particles to new random values
     */
    void seedParticles();

};

} // namespace PSO

#endif // __SWARM__
