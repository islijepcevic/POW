#!/bin/bash

cd PSO

#./compile.sh
make
RES=$?

cd ..

if [ $RES = 0 ]; then
    echo "RUN"
    mpiexec -n 1 python2 POW.py Simple.py input_simple
fi
