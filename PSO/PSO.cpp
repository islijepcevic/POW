/*
 * PSO.cpp
 *
 * class that implements Particle Swarm Optimization algorithm
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PSO.hpp"

#include <cmath>
#include "NeighbourhoodFactory.hpp"
#include "PotentialRepulsionField.hpp"
#include "EmptyRepulsionField.hpp"
#include "randomUtils.hpp"

#include <cstdio>

// index for dummy particle
#define DUMMY_INDEX      -1
// mpi tag to signal normal send of a particle
#define SEND_TAG        100
// mpi tag to signal that next receive is neighbourhood bcast
#define ITER_BCAST_TAG  101
// mpi tag to signal to workers that algorithm is over
#define DIE_TAG         102
// mpi tag to signal that worker is done
#define WORK_DONE_TAG   200

namespace PSO {

PSO::PSO(PsoParameters& _params, PsoSpace* _space,
            AbstractFitnessProxy& _fitness, MPI_Comm _comm) :
    params(_params),
    space(_space),
    fitness(_fitness),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(),
    neighbourhood(),
    repulsionField(),
    totalSteps(params.getIntParam("max_steps")),
    totalRepetitions(params.getIntParam("repeat")),
    inertiaMax(params.getDoubleParam("inertia_max")),
    inertiaMin(params.getDoubleParam("inertia_min")),
    inertia(inertiaMax),
    bestParticle(DUMMY_INDEX, space->getNoDimensions()) {

    // this constructor is called from rank 0 anyway
    if (mpiWorld.rank() == 0) {

//        printf("master sending space\n");
//        broadcast(mpiWorld, space, 0);
//        printf("master sent space\n");

        swarm = Swarm(params.getIntParam("n_particles"), *space);

        neighbourhood = createNeighbourhood(
             params.getStringParam("neigh_type"),
             swarm,
             params.getIntParam("neigh_size")
        );

        if (params.getStringParam("repel").compare("True")) {
                repulsionField = new PotentialRepulsionField(
                    params.getDoubleParam("repel_factor")
                );
        } else {
            repulsionField = new EmptyRepulsionField();
        }

        // mpi send skeletons
    }
}

PSO::~PSO() {
    // space and fitness will be freed in Python (automatically)
    if (neighbourhood != NULL) {
        delete neighbourhood;
    }

    delete repulsionField;
}

/*********************************************************************
 * GETTERS / SETTERS / REGISTER FOR OBSERVERS
 *******************************************************************/

const Swarm& PSO::getSwarm() const {
    return swarm;
}

const Particle& PSO::getBestParticle() const {
    return bestParticle;
}

void PSO::registerPrinterObserver(AbstractPrinter* printer) {
    printers.push_back(printer);
}

/*
 * main launch
 */
void PSO::launch() {

    mpiWorld.barrier();

    initRandomSeed();

    if (mpiWorld.rank() == 0) {
        manager();
    } else {
        worker();
    }

}

/*********************************************************************
 * MANAGER METHODS IMPLEMENTATION
 *******************************************************************/

/*
 * main code for rank 0
 */
void PSO::manager() {

    Particle dummmyParticle(DUMMY_INDEX, space->getNoDimensions());
    Particle workingParticle(DUMMY_INDEX, space->getNoDimensions());
    boost::mpi::status status;

    // loop that repeats executing PSO algorithm
    for (int repeatNo = 0; repeatNo < totalRepetitions; repeatNo++) {
        // print using observers
        for (std::list<AbstractPrinter*>::const_iterator printIterator
                = printers.begin(); printIterator != printers.end();
                printIterator++) {
            (*printIterator)->printRepetitionStart(*this, repeatNo);
        }

        // seed all the particles in the swarm
        swarm.seedParticles();
        bestParticle.seed(*space);

        // main loop for a single PSO launch
        for (int step = 0; step < totalSteps; step++) {

            // print using observers
            for (std::list<AbstractPrinter*>::const_iterator printIterator
                    = printers.begin(); printIterator != printers.end();
                    printIterator++) {
                (*printIterator)->printIterationStart(*this, repeatNo, step);
            }

            // rescale inertia factor
            inertia = inertiaMax
                - (double)step / totalSteps * (inertiaMax - inertiaMin);

            // update neighbourhood
            neighbourhood->scanNeighbours(swarm);

            // notify all workers about neighbourhood bcast
            for (int i = 1; i < mpiWorld.size(); i++) {
                mpiWorld.isend(i, ITER_BCAST_TAG, dummmyParticle);
            }
            mpiWorld.barrier();
            broadcast(mpiWorld, neighbourhood, 0);
            broadcast(mpiWorld, inertia, 0);
            broadcast(mpiWorld, repulsionField, 0);

            // MAIN PART OF ALGORITHM - UPDATE ALL PARTICLES IN SWARM
            int nParticlesSent = 0;
            int totalParticles = swarm.getNoParticles();

            // SEND PARTICLES TO ALL WORKERS
            for (int i = 1; i < mpiWorld.size(); i++) {
                mpiWorld.isend(i, SEND_TAG, swarm.getParticle(nParticlesSent));

                nParticlesSent++;
                if (nParticlesSent >= totalParticles) {
                    break;
                }
            }

            // WHEN WORKER IS FINISHED, SEND HIM ANOTHER PARTICLE
            while (nParticlesSent < totalParticles) {
                status = mpiWorld.recv(
                    boost::mpi::any_source, WORK_DONE_TAG, workingParticle
                );
                checkRepel(workingParticle);
                swarm.setParticle(workingParticle);

                checkBest(workingParticle);

                mpiWorld.send(
                    status.source(), SEND_TAG, swarm.getParticle(nParticlesSent)
                );
        
                nParticlesSent++;
            }

            // GET ALL PARTICLES BACK
            int nParticlesReceived = 0;
            for (int i = 1; i < mpiWorld.size(); i++) {
                mpiWorld.recv(
                    boost::mpi::any_source, WORK_DONE_TAG, workingParticle
                );
                checkRepel(workingParticle);
                swarm.setParticle(workingParticle);

                checkBest(workingParticle);

                nParticlesReceived++;
                if (nParticlesReceived >= totalParticles) {
                    break;
                }
            }

            // print using observers
            for (std::list<AbstractPrinter*>::const_iterator printIterator
                    = printers.begin(); printIterator != printers.end();
                    printIterator++) {
                (*printIterator)->printIterationEnd(*this, repeatNo, step);
            }
        } // end iteration
    } // end repeat

    // SHUTDOWN WORKERS
    for (int i = 1; i < mpiWorld.size(); i++) {
        mpiWorld.isend(i, DIE_TAG, dummmyParticle);
    }

    // call close on all printers
    for (std::list<AbstractPrinter*>::const_iterator printIterator
            = printers.begin(); printIterator != printers.end();
            printIterator++) {
        (*printIterator)->close();
    }
}

void PSO::checkBest(const Particle& newParticle) {
    if (newParticle.currentValue < bestParticle.currentValue) {
        bestParticle = newParticle;

        // just a little bit of precaution
        if (bestParticle.currentValue != bestParticle.bestValue) {
            throw "best particle exception";
        }
    }
}

void PSO::checkRepel(Particle& particle) {
    if (particle.getRepelFlag()) {
        repulsionField->addRepeller(particle.oldPosition);
        particle.clearRepelFlag();
    }
}

/*********************************************************************
 * WORKERS' METHODS IMPLEMENTATION
 *******************************************************************/

/*
 * main code for every other node
 */
void PSO::worker() {

    Particle particle;

    boost::mpi::status status;

    while (true) {

        status = mpiWorld.recv(0, boost::mpi::any_tag, particle);

        if (status.tag() == ITER_BCAST_TAG) {
            mpiWorld.barrier();
            broadcast(mpiWorld, neighbourhood, 0);
            broadcast(mpiWorld, inertia, 0);
            broadcast(mpiWorld, repulsionField, 0);
            continue;

        } else if (status.tag() == DIE_TAG) {
            break;
        }

        updateParticle(particle);

        mpiWorld.send(0, WORK_DONE_TAG, particle);
    }
}

void PSO::updateParticle(Particle& particle) {

    particle.oldPosition = particle.currentPosition;

    // velocity
    updateVelocity(particle);
    double velocityVal = particle.getVelocityValue();

    // position, with KaR
    if (velocityVal > params.getDoubleParam("kar")) {
        particle.move();
        space->checkBoundaries(particle);

    } else { // KaR - when velocity is small
        particle.kick(*space); // kick anyway

        if (particle.currentValue > params.getDoubleParam("accept")) {
            particle.move();
            space->checkBoundaries(particle);
        } else {
            particle.reseed(*space); // reseed if current fitness good
        }
    }

    repulsionField->apply(particle, *space);
    
    // fitness
    fitness.evaluation(particle);

    if (particle.currentValue < particle.bestValue) {
        particle.bestValue = particle.currentValue;
        particle.bestPosition = particle.currentPosition;
    }
}

void PSO::updateVelocity(Particle& particle) {

    // factor of current velocity, multiplied by inertia
    std::vector<double> selfFactor = particle.currentVelocity;
    for (unsigned int i = 0; i < selfFactor.size(); i++) {
        selfFactor[i] *= inertia;
    }

    // factor of "local" best
    std::vector<double> personalFactor = space->calculateShortestDistanceVector(
        particle.currentPosition, particle.bestPosition
    );
    for (unsigned int i = 0; i < personalFactor.size(); i++) {
        personalFactor[i] *= params.getDoubleParam("cn") * randDouble(0.0, 1.0);
    }

    // factor of "global"/neighbourhood best
    const Particle& bestNeighbour = neighbourhood->findBestNeighbour(
        particle.getIndex()
    );
    std::vector<double> nhoodFactor = space->calculateShortestDistanceVector(
        particle.currentPosition, bestNeighbour.bestPosition
    );
    for (unsigned int i = 0; i < nhoodFactor.size(); i++) {
        nhoodFactor[i] *= params.getDoubleParam("cp") * randDouble(0.0, 1.0);
    }

    // sum all factors to get new velocity
    for (unsigned int i = 0; i < particle.currentVelocity.size(); i++) {
        double newVel = selfFactor[i] + personalFactor[i] + nhoodFactor[i];
        if (fabs(newVel) > space->getSize(i)) {
            // copysign takes magnitude of first argument, and sign of second
            newVel = copysign(space->getSize(i), newVel);
        }

        particle.currentVelocity[i] = newVel;
    }
}

} // namespace PSO
