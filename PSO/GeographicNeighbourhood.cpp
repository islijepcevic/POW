/*
 * GeographicNeighbourhood.cpp
 *
 * a class representing geometric local neighbourhood
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "GeographicNeighbourhood.hpp"

#include "Swarm.hpp"
#include "PsoSpace.hpp"
#include "constants.hpp"
#include <utility>
#include <algorithm>

namespace PSO {

GeographicNeighbourhood::GeographicNeighbourhood() {
}

GeographicNeighbourhood::GeographicNeighbourhood(
        int nParticles, int _nhoodSize) :
            bestNeighbours(),
            nhoodSize(_nhoodSize) {

    bestNeighbours.reserve(nParticles);
    if (nhoodSize + 1 > nParticles) {
        nhoodSize = nParticles - 1;
    }
}

GeographicNeighbourhood::~GeographicNeighbourhood() {
}

void GeographicNeighbourhood::scanNeighbours(const Swarm& swarm) {
    int noParticles = swarm.getNoParticles();

    const PsoSpace& space = swarm.getSpace();

    // this will be computed for each particle
    // pair is: <distance (from a given particle), index>
    std::vector< std::pair<double, double> > neighbourhood;
    neighbourhood.resize( noParticles-1, std::make_pair(0.0, 0.0) );

    // iterate through every particle
    for (int partIndex = 0; partIndex < noParticles; partIndex++) {
        for (int otherIndex = 0; otherIndex < noParticles; otherIndex++) {

            std::vector<double> distVect =
                space.calculateShortestDistanceVector(
                    swarm.getParticle(partIndex), swarm.getParticle(otherIndex)
                );
            double squareSum = 0.0;
            for (int i = 0; i < distVect.size(); i++) {
                squareSum += (distVect[i] * distVect[i]);
            }
            
            neighbourhood[otherIndex] = std::make_pair(
                squareSum, swarm.getParticle(otherIndex).bestValue
            );
        }
        
        std::sort(neighbourhood.begin(), neighbourhood.end());

        // choose best from the neighbourhood
        int bestIndex = 0;
        double bestValue = VERY_LARGE_VALUE;

        // choose size of neighbourhood plus 1 for the particle itself
        int size = nhoodSize + 1;
        for (int i = 0; i <= size; i++) {
            int index = neighbourhood[i].second;
            double value = swarm.getParticle(index).bestValue;
            if (value < bestValue) {
                bestValue = value;
                bestIndex = index;
            }
        }
        bestNeighbours[partIndex] = swarm.getParticle(bestIndex);
    }
}

const Particle& GeographicNeighbourhood::findBestNeighbour(int particleIndex)
        const {
    return bestNeighbours[particleIndex];
}

} // namespace PSO