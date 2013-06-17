#!/bin/bash

#echo "RUN"
echo 'mpiexec -n 3 python2 POW.py Simple.py input_simple'
mpiexec -n 3 python2 POW.py Simple.py input_simple
