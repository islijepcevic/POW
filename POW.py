#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (c) 2012 EPFL (Ecole Polytechnique federale de Lausanne)
# Laboratory for Biomolecular Modeling, School of Life Sciences
#
# POW is free software ;
# you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation ;
# either version 2 of the License, or (at your option) any later version.
# POW is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY ;
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# You should have received a copy of the GNU General Public License along with POW ;
# if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
#
# Author : Matteo Degiacomi, matteothomas.degiacomi@epfl.ch
# Web site : http://lbm.epfl.ch


from PSO.PSO import PSO, PsoParameters

#import wx
import os, sys
import time
import numpy as np
#import ClusterAndDraw as CnD

from Default import StdPrinter, LogPrinter

from mpi4py import MPI
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

#check wether an appropriate number of parameters has been provided
if rank == 0:

    print '\n>        Parallel Optimization Workbench (POW)         <'
    print   '> (c) 2012, Laboratory for Biomolecular Modeling, EPFL <'

    # checking if input is correct and has 3 arguments
    if len(sys.argv)!=3:
        print "\nERROR: expected 2 parameters as input!"
        print "USAGE: mpiexec -n 2 POW.py module_name input_file\n"
        sys.exit(1)

#get input file
infile=str(sys.argv[2])

# ----- EXITING FROM ERROR
if rank == 0 and os.path.isfile(infile)!=1 :
    print "ERROR: input file not found!"
    sys.exit(1)
# -----

#get program installation location and declare an environment variable
#   (needed by some modules)
h=os.path.dirname(sys.argv[0])
home_dir=os.path.abspath(str(h))
os.environ['POW']=home_dir
sys.path.append(home_dir)

#get local working directory and add to pythonpath
working_dir=os.getcwd()
sys.path.append(working_dir)

#add module path in path, in case it's not in POW home
p,mod=os.path.split(sys.argv[1])
if len(p)>0:
    sys.path.append(p)

#preprocessing performed only by master node
if rank == 0:

    #init timer
    start=time.time()

    print '\n> PREPROCESSING %s\n'%mod.split('.')[0]

    mode = None # added by Ivan so that pylintig doesn't scream
    exec 'import %s as mode'%(mod.split('.')[0]) 

    #parse input file
    print '>> parsing input file...'
    params=mode.Parser() 
    params.add_standard() 
    params.set_default_values() 
    params.parse(infile) 
    params.check_standard_variables() 
    params.check_variables() 

    # init params that are used in c++
    psoParams = PsoParameters()
    params.addAllToPsoParams(psoParams)

    #load requested data structures
    print '>> importing data...'
    data=mode.Data(params)

    #build search space
    print ">> generating search space..."
    space=mode.Space(params,data)
    print ">> "+str(len(space.low))+"D space generated (min_pos, max_pos):"
    for i in xrange(0,len(space.low),1):
        print "   %s, %s"%(space.low[i],space.high[i])

    #charge module fitness function or the one requested by user
    if params.fit=="NA":
        print ">> creating fitness function..."
        fitness=mode.Fitness(data,params)
    else:
        print ">>> importing user defined fitness function"
        try:
            user_fit = None
            exec 'import %s as user_fit'%(params.fit.split('.')[0])
        except ImportError, e:
            print "ERROR: load of user defined fitness function failed!"
            sys.exit(1)
        try:
            user_fit.Fitness
        except NameError:
            print 'ERROR: user defined fitness function file should contain' \
                'a class Fitness with a function evaluate(id,values_array) '
        fitness=user_fit.Fitness(data,params)

    if params.dimensions != space.cell_size:
        print >> sys.stderr, "params.dimensions and space.cell_size DIFFER;", \
                            "updating params.dimensions accordingly"

        params.dimensions = space.cell_size

else:
    params=None
    data=None
    space=None
    fitness=None
    post = None

#propagate parameters, data, space and fitness function to slaves
comm.Barrier()
params=comm.bcast(params,root=0)
#space=comm.bcast(space,root=0)      # removed by Ivan
#fitness=comm.bcast(fitness,root=0)  # removed by Ivan
data=comm.bcast(data,root=0)
comm.Barrier()

#prepare optimizer
if rank == 0:
    pSpace = space.createPsoSpace()

    search=PSO(psoParams,pSpace,fitness, comm)

    # register different types of printers
    stdPrinter = StdPrinter()
    search.registerPrinterObserver(stdPrinter)

    logPrinter = LogPrinter(params)
    search.registerPrinterObserver(logPrinter)

else:
    search=PSO()

#init optimization timer
if rank==0:
    start2=time.time()

search.launch()
comm.Barrier()

if rank==0:
    end2=time.time()
    one_step=end2-start2
    print(">> optimization time (sec): {t:<8.3f}".format(t=one_step))

    #postprocess
    print '\n> POSTPROCESSING...'
    post=mode.Postprocess(data,params)
    
comm.Barrier()
post=comm.bcast( post,root=0)
comm.Barrier()
    
post.run() # Now replaced by creating the distance matrix

if rank == 0:
    end=time.time()
    one_step=end-start
    print("\n>> total execution time (sec): {t:<8.3f}\n".format(t=one_step))
