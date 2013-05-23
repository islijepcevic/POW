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

AbstractSpace.o: AbstractSpace.cpp
	$(CC) $(CFLAGS) AbstractSpace.cpp -o AbstractSpace.o

PsoParameters.o: PsoParameters.cpp
	$(CC) $(CFLAGS) PsoParameters.cpp -o PsoParameters.o

randomUtils.o: randomUtils.cpp
	$(CC) $(CFLAGS) randomUtils.cpp -o randomUtils.o

Particle.o: Particle.cpp randomUtils.o
	$(CC) $(CFLAGS) Particle.cpp -o Particle.o

PSO.o: PSO.cpp AbstractSpace.o
	$(CC) $(CFLAGS) PSO.cpp -o PSO.o

PSO_wrap.o: PSO_wrap.cxx PSO.o AbstractSpace.o PsoParameters.o Particle.o
	$(CC) $(CFLAGS) PSO_wrap.cxx -I$(PYDIR) -I$(MPI4PY)

_PSO.so: PSO_wrap.o AbstractSpace.o PsoParameters.o PSO.o Particle.o randomUtils.o
	$(CC) $(LDFLAGS) -o _PSO.so PSO_wrap.o AbstractSpace.o Particle.o \
	    PsoParameters.o PSO.o randomUtils.o

clean:
	\rm -f *.o  *~ PSO_wrap.*

