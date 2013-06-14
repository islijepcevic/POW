/*
 * PSO.cpp
 *
 * class that implements Particle Swarm Optimization algorithm
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PSO.hpp"

// temporary include
#include <cstdio>
#include <iostream>
#include "NeighbourhoodFactory.hpp"

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

PSO::PSO(PsoSpace* _space, AbstractFitnessProxy& _fitness, MPI_Comm _comm) :
    params(),
    space(_space),
    fitness(_fitness),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(), 
    neighbourhood(),
    totalSteps(),
    inertiaMax(),
    inertiaMin(),
    inertia() {

    if (mpiWorld.rank() != 0) {
//        printf("slave waiting for space\n");
//        broadcast(mpiWorld, space, 0);
//        printf("slave has space\n");
    }
}

PSO::PSO(PsoParameters& _params, PsoSpace* _space,
            AbstractFitnessProxy& _fitness, MPI_Comm _comm) :
    params(_params),
    space(_space),
    fitness(_fitness),
    mpiWorld(_comm, boost::mpi::comm_attach),
    swarm(),
    neighbourhood(NULL),
    totalSteps(params.getIntParam("max_steps")),
    totalRepetitions(params.getIntParam("repeat")),
    inertiaMax(params.getDoubleParam("inertia_max")),
    inertiaMin(params.getDoubleParam("inertia_min")),
    inertia(inertiaMax) {

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

        // mpi send skeletons
    }
}

PSO::~PSO() {
    // space and fitness will be freed in Python (automatically)
    if (neighbourhood != NULL) {
        delete neighbourhood;
    }
}

void PSO::registerPrinterObserver(AbstractPrinter* printer) {
    printers.push_back(printer);
}

/*
 * main launch
 *
 * RANK IS ONLY PARAMETER HERE FOR TESTING PURPOSES - REMOVE IT WHEN REAL
 * MPI TAKES THE PLACE
 */
void PSO::launch() {

    mpiWorld.barrier();

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
            (*printIterator)->printRepetitionStart(*this);
        }

        // seed all the particles in the swarm
        swarm.seedParticles();

        // main loop for one PSO launch
        for (int step = 0; step < totalSteps; step++) {

            // print using observers
            for (std::list<AbstractPrinter*>::const_iterator printIterator
                    = printers.begin(); printIterator != printers.end();
                    printIterator++) {
                (*printIterator)->printIterationStart(*this);
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
                swarm.setParticle(workingParticle);

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
                swarm.setParticle(workingParticle);

                nParticlesReceived++;
                if (nParticlesReceived >= totalParticles) {
                    break;
                }
            }

            // print using observers
            for (std::list<AbstractPrinter*>::const_iterator printIterator
                    = printers.begin(); printIterator != printers.end();
                    printIterator++) {
                (*printIterator)->printIterationEnd(*this);
            }
        } // end iteration
    } // end repeat

    // SHUTDOWN WORKERS
    for (int i = 1; i < mpiWorld.size(); i++) {
        mpiWorld.isend(i, DIE_TAG, dummmyParticle);
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
            continue;

        } else if (status.tag() == DIE_TAG) {
            break;
        }

        updateParticle(particle);

        mpiWorld.send(0, WORK_DONE_TAG, particle);
    }
}

void PSO::updateParticle(Particle& particle) {
    // TODO
}

} // namespace PSO
