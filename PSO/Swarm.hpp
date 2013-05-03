/*
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

#include "Particle.hpp"

namespace PSO {

class Swarm {
protected:

    // array of all particles
    std::vector<Particle> particles;

    // reference to space
    AbstractSpace& space;

public:

    /*
     * constructor of the Swarm
     */
    Swarm(int noParticles, AbstractSpace& _space);

    /*
     * destructor of the Swarm
     */
    ~Swarm();

    /*
     * getter for the number of particles
     * @return - number of particles
     */
    int getNoParticles() const;

    /*
     * getter for the space
     * @return - reference to the space object
     */
    AbstractSpace& getSpace() const;

    /*
     * getter for a particular particle
     * @param index - index of the particle
     * @return - reference to the index-th particle
     */
    Particle& getParticle(int index) const;

    /*
     * method that seeds particles to new random values
     */
    void seedParticles();

};

} // namespace PSO

#endif // __SWARM__
