
# run with:
# mpiexec -n <N> Simple.py input_simple

from Default import Parser as P
from Default import Space as S
from Default import Postprocess as PP
from Default import BaseFitness as BF

import numpy as np
import sys


class Fitness(BF):

    def __init__(self,data,params):
        BF.__init__(self)

    def evaluate(self,num,pos):
        if type(pos) != np.ndarray:
            pos = np.array(pos)

        #return 10*len(pos) + np.sum(pos**2 - 10*np.cos(2*np.pi*pos))
        return 10*len(pos)+np.sum(pos**2-10*np.cos(2*np.pi*pos))

class Space(S):
    def __init__(self, params, data):
        S.__init__(self)

        # assign low boundaries
        if params.low_input!="NA" :
            self.low=np.zeros(len(params.low_input))
            for i in xrange(0,len(params.low_input),1):
                self.low[i]=params.low_input[i]
        else:
            print "ERROR: boundaryMin should be defined"
            sys.exit(1) 
        
        # assign high boundaries
        if params.high_input!="NA" :
            self.high=np.zeros(len(params.low_input))
            for i in xrange(0,len(params.high_input),1):
                self.high[i]=params.high_input[i]
        else:
            print "ERROR: boundaryMax should be defined"
            sys.exit(1)
                              
        # set boundary type (default is periodic)
        self.boundary_type=np.zeros(len(params.low_input)) + 1
        if params.boundary_type[0]!="NA":
            for i in xrange(0,len(params.low_input),1):
             	self.boundary_type[i]=params.boundary_type[i] 


class Parser(P):
    def __init__(self):
        P.__init__(self)

    def check_variables(self):
        '''
        this method is for checking additional variables, introduced by module
        programmer
        '''
        pass

class Data:
    def __init__(self,params):
        pass      

class Postprocess(PP):

    def __init__(self,data,params):
        pass

    def run(self) :
        pass    
