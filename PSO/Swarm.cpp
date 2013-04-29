/*
 * Swarm.cpp
 *
 * a class that contains the whole swarm of particles
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "Swarm.hpp"

#include <cstdlib>
#include <ctime>
#include "randomUtils.hpp"

#define VERY_LARGE_VALUE 100000000

namespace PSO {

Swarm::Swarm(int noParticles, AbstractSpace& _space) :
    particles( noParticles, Particle(_space.getNoDimensions()) ),
    space(_space) {

    srand(time(NULL));
}

Swarm::~Swarm() {
}

int Swarm::getNoParticles() const {
    return particles.size();
}

AbstractSpace& Swarm::getSpace() const {
    return space;
}

Particle& Swarm::getParticle(int index) const {
    return particles[i];
}

void Swarm::seedParticles() {

    for (int i = 0; i < particles.size(); i++) {
        particles[i].seed();
    }
}


} // namespace PSO
