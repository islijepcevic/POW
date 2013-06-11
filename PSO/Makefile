#! /usr/bin/env make

CC=mpic++
CFLAGS= -O2 -fPIC -c -lm -Wall -ggdb
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

PsoSpace.o: PsoSpace.cpp PsoSpace.hpp
	$(CC) $(CFLAGS) PsoSpace.cpp -o PsoSpace.o

PsoParameters.o: PsoParameters.cpp PsoParameters.hpp
	$(CC) $(CFLAGS) PsoParameters.cpp -o PsoParameters.o

randomUtils.o: randomUtils.cpp randomUtils.hpp
	$(CC) $(CFLAGS) randomUtils.cpp -o randomUtils.o

Particle.o: Particle.cpp Particle.hpp PsoSpace.hpp constants.hpp \
    randomUtils.hpp
	$(CC) $(CFLAGS) Particle.cpp -o Particle.o $(BOOSTSERIAL)

Dimension.o: Dimension.cpp Dimension.hpp
	$(CC) $(CFLAGS) Dimension.cpp -o Dimension.o

PeriodicDimension.o: PeriodicDimension.cpp PeriodicDimension.hpp
	$(CC) $(CFLAGS) PeriodicDimension.cpp -o PeriodicDimension.o

ReflexiveDimension.o: ReflexiveDimension.cpp ReflexiveDimension.hpp
	$(CC) $(CFLAGS) ReflexiveDimension.cpp -o ReflexiveDimension.o

SpaceFactory.o: SpaceFactory.cpp SpaceFactory.hpp Dimension.hpp \
    PeriodicDimension.hpp ReflexiveDimension.hpp
	$(CC) $(CFLAGS) SpaceFactory.cpp -o SpaceFactory.o

Swarm.o: Swarm.cpp Swarm.hpp randomUtils.hpp
	$(CC) $(CFLAGS) Swarm.cpp -o Swarm.o

IndexedNeighbourhood.o: IndexedNeighbourhood.cpp IndexedNeighbourhood.hpp \
    Swarm.hpp constants.hpp
	$(CC) $(CFLAGS) IndexedNeighbourhood.cpp -o IndexedNeighbourhood.o \
	    $(BOOSTSERIAL)

GeographicNeighbourhood.o: GeographicNeighbourhood.cpp \
    GeographicNeighbourhood.hpp Swarm.hpp PsoSpace.hpp constants.hpp
	$(CC) $(CFLAGS) GeographicNeighbourhood.cpp -o \
	    GeographicNeighbourhood.o $(BOOSTSERIAL)

NeighbourhoodFactory.o: NeighbourhoodFactory.cpp NeighbourhoodFactory.hpp \
    GeographicNeighbourhood.hpp IndexedNeighbourhood.hpp
	$(CC) $(CFLAGS) NeighbourhoodFactory.cpp -o NeighbourhoodFactory.o

PSO.o: PSO.cpp PSO.hpp NeighbourhoodFactory.hpp
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

clean:
	\rm -f *.o  *~ PSO_wrap.*

# HEADER FILES
AbstractFitness.hpp: Particle.hpp

AbstractPrinter.hpp: PSOForward.hpp

GeographicNeighbourhood.hpp: Neighbourhood.hpp

IndexedNeighbourhood.hpp: Neighbourhood.hpp

NeighbourhoodFactory.hpp: Swarm.hpp

Neighbourhood.hpp: SwarmForward.hpp Particle.hpp

Particle.hpp: PsoSpaceForward.hpp

PeriodicDimension.hpp: Dimension.hpp

PSO.hpp: PsoParameters.hpp PsoSpace.hpp AbstractFitness.hpp \
    AbstractPrinter.hpp Swarm.hpp Neighbourhood.hpp

PsoSpace.hpp: Particle.hpp Dimension.hpp

ReflexiveDimension.hpp: Dimension.hpp

SpaceFactory.hpp: PsoSpace.hpp

Swarm.hpp: Particle.hpp PsoSpace.hpp 
