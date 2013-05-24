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

namespace PSO {

Swarm::Swarm() {
}

Swarm::Swarm(int noParticles, PsoSpace& _space) :
    particles( noParticles, Particle(_space.getNoDimensions()) ),
    space(_space),
    inertia(0.0) {

    // initialize random seed
    initRandomSeed();
}

Swarm::~Swarm() {
}

int Swarm::getNoParticles() const {
    return particles.size();
}

PsoSpace& Swarm::getSpace() const {
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
