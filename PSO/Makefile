#! /usr/bin/env make

CC=mpic++
CFLAGS= -O2 -fPIC -c -lm -ggdb
LDFLAGS= -shared

PYDIR=/usr/include/python2.7
MPI4PY=/usr/lib/python2.7/site-packages/mpi4py/include

SWIG=swig
SWIGFLAGS= -c++ -python -I$(MPI4PY)

BOOSTSERIAL= -lboost_serialization
BOOSTMPI= -I/usr/include/boost/mpi -Llibdir -lboost_mpi $(BOOSTSERIAL)

all: _PSO.so

PSO_wrap.cxx: PSO.i *.hpp
	$(SWIG) $(SWIGFLAGS) PSO.i

PsoSpace.o: PsoSpace.cpp hppPsoSpace
	$(CC) $(CFLAGS) PsoSpace.cpp -o PsoSpace.o

PsoParameters.o: PsoParameters.cpp hppPsoParameters
	$(CC) $(CFLAGS) PsoParameters.cpp -o PsoParameters.o

randomUtils.o: randomUtils.cpp hppRandomUtils
	$(CC) $(CFLAGS) randomUtils.cpp -o randomUtils.o

Particle.o: Particle.cpp hppParticle hppPsoSpace hppConstants hppRandomUtils
	$(CC) $(CFLAGS) Particle.cpp -o Particle.o $(BOOSTSERIAL)

Dimension.o: Dimension.cpp hppDimension
	$(CC) $(CFLAGS) Dimension.cpp -o Dimension.o

PeriodicDimension.o: PeriodicDimension.cpp hppPeriodicDimension
	$(CC) $(CFLAGS) PeriodicDimension.cpp -o PeriodicDimension.o

ReflexiveDimension.o: ReflexiveDimension.cpp hppReflexiveDimension
	$(CC) $(CFLAGS) ReflexiveDimension.cpp -o ReflexiveDimension.o

SpaceFactory.o: SpaceFactory.cpp hppSpaceFactory hppDimension \
    hppPeriodicDimension hppReflexiveDimension
	$(CC) $(CFLAGS) SpaceFactory.cpp -o SpaceFactory.o

Swarm.o: Swarm.cpp hppSwarm hppRandomUtils
	$(CC) $(CFLAGS) Swarm.cpp -o Swarm.o

IndexedNeighbourhood.o: IndexedNeighbourhood.cpp hppIndexedNeighbourhood \
    hppSwarm hppConstants
	$(CC) $(CFLAGS) IndexedNeighbourhood.cpp -o IndexedNeighbourhood.o \
	    $(BOOSTSERIAL)

GeographicNeighbourhood.o: GeographicNeighbourhood.cpp \
    hppGeographicNeighbourhood hppSwarm hppPsoSpace hppConstants
	$(CC) $(CFLAGS) GeographicNeighbourhood.cpp -o \
	    GeographicNeighbourhood.o $(BOOSTSERIAL)

NeighbourhoodFactory.o: NeighbourhoodFactory.cpp hppNeighbourhoodFactory \
    hppGeographicNeighbourhood hppIndexedNeighbourhood
	$(CC) $(CFLAGS) NeighbourhoodFactory.cpp -o NeighbourhoodFactory.o

PSO.o: PSO.cpp hppPSO hppNeighbourhoodFactory
	$(CC) $(CFLAGS) PSO.cpp -o PSO.o $(BOOSTMPI)

PSO_wrap.o: PSO_wrap.cxx PSO.o PsoSpace.o PsoParameters.o Particle.o \
    randomUtils.o Dimension.o PeriodicDimension.o ReflexiveDimension.o \
    SpaceFactory.o Swarm.o GeographicNeighbourhood.o IndexedNeighbourhood.o \
    NeighbourhoodFactory.o
	$(CC) $(CFLAGS) PSO_wrap.cxx -I$(PYDIR) -I$(MPI4PY) $(BOOSTMPI)

_PSO.so: PSO_wrap.o
	$(CC) $(LDFLAGS) $(BOOSTMPI) -o _PSO.so PSO_wrap.o PsoSpace.o \
	    Particle.o PsoParameters.o PSO.o randomUtils.o Dimension.o \
	    SpaceFactory.o PeriodicDimension.o ReflexiveDimension.o Swarm.o \
	    GeographicNeighbourhood.o IndexedNeighbourhood.o \
	    NeighbourhoodFactory.o

hppAbstractFitness: AbstractFitness.hpp Particle.hpp

hppAbstractPrinter: AbstractPrinter.hpp PSOForward.hpp

hppConstants: constants.hpp

hppDimension: Dimension.hpp

hppGeographicNeighbourhood: GeographicNeighbourhood.hpp Neighbourhood.hpp

hppIndexedNeighbourhood: IndexedNeighbourhood.hpp Neighbourhood.hpp

hppNeighbourhoodFactory: NeighbourhoodFactory.hpp Swarm.hpp

hppNeighbourhood: Neighbourhood.hpp SwarmForward.hpp Particle.hpp

hppParticle: Particle.hpp PsoSpaceForward.hpp

hppPeriodicDimension: PeriodicDimension.hpp Dimension.hpp

hppPSO: PSO.hpp PsoParameters.hpp PsoSpace.hpp AbstractFitness.hpp \
    AbstractPrinter.hpp Swarm.hpp Neighbourhood.hpp

hppPsoParameters: PsoParameters.hpp

hppPsoSpace: PsoSpace.hpp Particle.hpp Dimension.hpp

hppRandomUtils: randomUtils.hpp

hppReflexiveDimension: ReflexiveDimension.hpp Dimension.hpp

hppSpaceFactory: SpaceFactory.hpp PsoSpace.hpp

hppSwarm: Swarm.hpp Particle.hpp PsoSpace.hpp 

clean:
	\rm -f *.o  *~ PSO_wrap.*

