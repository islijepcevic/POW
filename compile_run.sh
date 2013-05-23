#!/bin/bash

cd PSO

#./compile.sh
make

cd ..

echo "RUN"
mpiexec -n 4 python2 POW.py Simple.py input_simple
