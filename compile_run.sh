#!/bin/bash

cd PSO

#./compile.sh
make
RES=$?

cd ..

if [ $RES = 0 ]; then
    echo
    echo 'RUN: mpiexec -n 3 python2 POW.py Simple.py input_simple'
    mpiexec -n 3 python2 POW.py Simple.py input_simple
fi
