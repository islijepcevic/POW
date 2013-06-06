/*
 * IndexedNeighbourhood.cpp
 *
 * a class representing indexed local neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "IndexedNeighbourhood.hpp"

#include "constants.hpp"
#include "Swarm.hpp"

#include <cstdio>
#include <iostream>

namespace PSO {

IndexedNeighbourhood::IndexedNeighbourhood() {
}

IndexedNeighbourhood::IndexedNeighbourhood(int nParticles, int _nhoodSize) :
    bestNeighbours(),
    nhoodSize(_nhoodSize) {

    if (2*nhoodSize + 1 > nParticles) {
        nhoodSize = (nParticles - 1) / 2;
    }

    bestNeighbours.resize(nParticles);
}

IndexedNeighbourhood::~IndexedNeighbourhood() {
}

void IndexedNeighbourhood::scanNeighbours(const Swarm& swarm) {

    int noParticles = swarm.getNoParticles();
    for (int partIndex = 0; partIndex < noParticles; partIndex++) {

        printf("PETLJAM PO PARTICLIMA %d\n", partIndex);

        int startIndex = (partIndex - nhoodSize);
        int endIndex = (partIndex + nhoodSize);

        int bestIndex = startIndex;
        double bestValue = VERY_LARGE_VALUE;

        // search the neighbourhood
        for (int iter = startIndex; iter <= endIndex; iter++) {
            // this needs to be done like that because % operator in c++ is 
            // defined like shit (and even changes with different compilers)
            int index = (iter + noParticles) % noParticles;
            double value = swarm.getParticle(index).bestValue;

            if (value < bestValue)  {
                bestValue = value;
                bestIndex = index;
            } } 
        printf("NASAO BEST\n");

        bestNeighbours[partIndex] = swarm.getParticle(bestIndex);
        printf("OCU DALJE\n");
    }
    printf("OCU VAN\n");
}

const Particle& IndexedNeighbourhood::findBestNeighbour(int particleIndex) const
{
    return bestNeighbours[particleIndex];
}

} // namespace PSO
