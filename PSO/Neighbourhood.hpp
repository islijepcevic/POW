/*
 * Neighbourhood.hpp
 *
 * an abstract class for representing particle neighbourhoood types
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __NEIGHBOURHOOD__
#define __NEIGHBOURHOOD__

#include <vector>

namespace PSO {

class Neighbourhood {
protected:

    Swarm& swarm;

public:

    Neighbourhood(const Swarm& _swarm) : swarm(_swarm) {}

    ~Neighbourhood();

    /*
     * scans all the necessary positions in the swarm, such that finding the
     * best neighbour can be fast
     */
    virtual void scanNeighbours() = 0;

    /*
     * finding the best evaluated neighbour for the given particle
     * @param particleIndex - index of a given particle in the swarm
     * @return - reference to the best evaluated particle
     */
    virtual Particle& findBestNeighbour(int particleIndex) const = 0;
};

} // namespace PSO

#endif // __NEIGHBOURHOOD__
