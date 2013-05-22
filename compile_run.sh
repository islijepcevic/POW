#!/bin/bash

cd PSO

./compile.sh

cd ..

echo "RUN"
mpiexec -n 1 python2 POW.py Simple.py input_simple
