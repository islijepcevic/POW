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

// workaround
PsoSpace dummySpace;

Swarm::Swarm() :
    particles(),
    space(dummySpace) {
}

Swarm::Swarm(int noParticles, PsoSpace& _space) :
    particles(),
    space(_space) {

    particles.reserve(noParticles);

    int noDim = space.getNoDimensions();
    for (int i = 0; i < noParticles; i++) {
        particles.push_back( Particle(i, noDim) );
    }

    // initialize random seed
    initRandomSeed();
}

Swarm::Swarm(const Swarm& _swarm) :
    particles(_swarm.particles),
    space(_swarm.space) {
}

Swarm::~Swarm() {
}

Swarm& Swarm::operator=(const Swarm& _swarm) {
    particles = _swarm.particles;
    space = _swarm.space;

    return *this;
}

int Swarm::getNoParticles() const {
    return particles.size();
}

const PsoSpace& Swarm::getSpace() const {
    return space;
}

Particle& Swarm::getParticle(int index) {
    return particles[index];
}

const Particle& Swarm::getParticle(int index) const {
    return particles[index];
}

void Swarm::seedParticles() {

    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i].seed(space);
    }
}

} // namespace PSO
