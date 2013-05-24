#! /usr/bin/env make

CC=mpic++
CFLAGS= -O2 -fPIC -c
LDFLAGS= -shared

PYDIR=/usr/include/python2.7
MPI4PY=/usr/lib/python2.7/site-packages/mpi4py/include

SWIG=swig
SWIGFLAGS= -c++ -python -I$(MPI4PY)

all: _PSO.so

PSO_wrap.cxx: PSO.i
	$(SWIG) $(SWIGFLAGS) PSO.i

PsoSpace.o: PsoSpace.cpp
	$(CC) $(CFLAGS) PsoSpace.cpp -o PsoSpace.o

PsoParameters.o: PsoParameters.cpp
	$(CC) $(CFLAGS) PsoParameters.cpp -o PsoParameters.o

randomUtils.o: randomUtils.cpp
	$(CC) $(CFLAGS) randomUtils.cpp -o randomUtils.o

Particle.o: Particle.cpp
	$(CC) $(CFLAGS) Particle.cpp -o Particle.o

Dimension.o: Dimension.cpp
	$(CC) $(CFLAGS) Dimension.cpp -o Dimension.o

PeriodicDimension.o: PeriodicDimension.cpp
	$(CC) $(CFLAGS) PeriodicDimension.cpp -o PeriodicDimension.o

ReflexiveDimension.o: ReflexiveDimension.cpp
	$(CC) $(CFLAGS) ReflexiveDimension.cpp -o ReflexiveDimension.o

SpaceFactory.o: SpaceFactory.cpp
	$(CC) $(CFLAGS) SpaceFactory.cpp -o SpaceFactory.o

PSO.o: PSO.cpp PsoSpace.o
	$(CC) $(CFLAGS) PSO.cpp -o PSO.o

PSO_wrap.o: PSO_wrap.cxx PSO.o PsoSpace.o PsoParameters.o Particle.o \
    randomUtils.o Dimension.o PeriodicDimension.o ReflexiveDimension.o \
    SpaceFactory.o
	$(CC) $(CFLAGS) PSO_wrap.cxx -I$(PYDIR) -I$(MPI4PY)

_PSO.so: PSO_wrap.o
	$(CC) $(LDFLAGS) -o _PSO.so PSO_wrap.o PsoSpace.o Particle.o \
	    PsoParameters.o PSO.o randomUtils.o Dimension.o SpaceFactory.o \
	    PeriodicDimension.o ReflexiveDimension.o

clean:
	\rm -f *.o  *~ PSO_wrap.*

