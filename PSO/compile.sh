#!/bin/bash

echo "SWIG"
swig -c++ -python -I/usr/lib/python2.7/site-packages/mpi4py/include PSO.i 

echo "COMPILE MY CPP"
mpic++ -O2 -fPIC -c AbstractSpace.cpp          #compiled
mpic++ -O2 -fPIC -c PsoParameters.cpp         #compiled
mpic++ -O2 -fPIC -c Dimension.cpp             #compiled
#mpic++ -O2 -fPIC -c GeometricNeighbourhood.cpp
#mpic++ -O2 -fPIC -c GlobalNeighbourhood.cpp   
#mpic++ -O2 -fPIC -c IndexedNeighbourhood.cpp  
#mpic++ -O2 -fPIC -c NeighbourhoodFactory.cpp  
mpic++ -O2 -fPIC -c Particle.cpp              #compiled
mpic++ -O2 -fPIC -c PeriodicDimension.cpp     
mpic++ -O2 -fPIC -c PSO.cpp                   #compiled
mpic++ -O2 -fPIC -c randomUtils.cpp           #compiled
mpic++ -O2 -fPIC -c ReflexiveDimension.cpp    
#mpic++ -O2 -fPIC -c Swarm.cpp                 

echo "COMPILE SWIG CPP"
mpic++ -O2 -fPIC -c PSO_wrap.cxx -I/usr/include/python2.7 \
    -I/usr/lib/python2.7/site-packages/mpi4py/include

echo "LINK"
mpic++ -shared -o _PSO.so PSO_wrap.o AbstractSpace.o PsoParameters.o \
    PSO.o Particle.o randomUtils.o
#    IndexedNeighbourhood.o NeighbourhoodFactory.o PeriodicDimension.o \
#    ReflexiveDimension.o Dimension.o GeometricNeighbourhood.o \
#    GlobalNeighbourhood.o Swarm.o
