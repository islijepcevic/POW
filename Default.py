'''
-*- coding: utf-8 -*-
Copyright (c) 2012 EPFL (Ecole Polytechnique federale de Lausanne)
Laboratory for Biomolecular Modeling, School of Life Sciences

POW is free software ;
you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation ;
either version 2 of the License, or (at your option) any later version.
POW is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY ;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with POW ;
if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.

Author : Matteo Degiacomi, matteothomas.degiacomi@epfl.ch
Modified by : Ivan Slijepcevic, ivan.slijepcevic@epfl.ch
Web site : http://lbm.epfl.ch
'''


import numpy as np
from copy import deepcopy
import os, sys

# integration with c++ code
from PSO.module import BaseParameters, AbstractFitness, AbstractSpace, \
        arrayToList

class Parser(BaseParameters): # this is imported in the file
    parameters={}

    def add_standard(self):


        #keyword_name, variable_name, type, default value
        self.add('repeat','repeat','int',1)
        self.add('steps','max_steps','int',200)
        self.add('particles','n_particles','int',80)
        self.add('neighborSize','neigh_size','int',1)
        self.add('neighborType','neigh_type','str',"indexed")
        self.add('filter_threshold','accept','float',0)
        self.add('inertiaMax','inertia_max','float',0.9)
        self.add('inertiaMin','inertia_min','float',0.4)
        # how much the velocity is influenced by global/neighborhood best
        self.add('cp','cp','float',2.0)
        # how much the velocity is influenced by personal best
        self.add('cn','cn','float',2.0) 
        self.add('output','output_file','str',"log.txt")
        self.add('dimensions','dimensions','int',-1)
        self.add('fitnessFile','fit','str',"NA")
        self.add('repulsion','repel','str',False)
        self.add('repulsion_factor','repel_factor', 'float', "NA")
        self.add('kar_threshold','kar','float',0.01)
        self.add('boundaryMin','low_input','array float',"NA")
        self.add('boundaryMax','high_input','array float',"NA")
        self.add('boundaryType','boundary_type','array str',np.array(["NA"]))
        self.add('load_restart','restart_load','str',"NA")
        self.add('save_restart','restart_save','str',"swarm.restart")
        self.add('restart_freq','restart_freq','int',0)


    def add(self,key,variable,vartype,default):
        '''
        insert a new keyword entry in parameters dictionary Xx enter all
        the tuples above in the self.parameter xX

        also fill in the maps in c++
        '''
        self.parameters[key]=[variable,vartype,default]

        # fill maps in c++ superclass
        if vartype == 'int':
            self.setIntParam(variable, default)
        elif vartype == 'float':
            self.setDoubleParam(variable, default)
        elif vartype == 'str':
            self.setStringParam(variable, default)
        elif vartype == 'aray int':
            self.setIntArrayParam(variable, default)
        elif vartype == 'array float':
            self.setDoubleArrayParam(variable, default)
        elif vartype == 'array str':
            self.setStringArrayParam(variable, default)
        else:
            print >> sys.stderr, "added parameter of non-default type"


    def set_default_values(self):
        '''
        set default values for all defined keywords Xx Parsing the self
        paramater and creating a self of all the values xX
        '''
        for k,v in self.parameters.iteritems():
            # this is where the self.style comes from
            exec 'self.%s=v[2]'%v[0] 


    #parse input file and replace default values
    def parse(self,infile):

        f = open(infile, 'r+')
        line = f.readline()
        while line:
            w = line.split()

            if len(w) > 0 and str(w[0][0])!='#':

            #val=[variable_name,variable_type,default_value] Xx same as the one above xX
                try:
                    val=self.parameters[w[0]] # -> get the default parameter of the value?
                except KeyError:
                    print "unrecognised keyword %s"%w[0]
                    sys.exit(1)

                #if type is string
                if val[1].split()[0]=='str': # _> val[1] = 'str' or 'int'
                    exec 'self.%s=%s("%s")'%(val[0],val[1],w[1]) # Xx here you are replacing the default by input paramater
                    # Xx exec -> self.restart_load = str("NA") xX the "NA" is from the input file
                #if type is int or float
                elif val[1].split()[0]=='int' or val[1].split()[0]=='float':
                    exec 'self.%s=%s(%s)'%(val[0],val[1],w[1])

                # GIORGIO_CODE in case the variable_name is a monomer or trajectory having multiple files (case of Hetero-multimer assembly)
                elif val[1].split()[0]=='array' and (val[1].split()[1]=='int' or val[1].split()[1]=='float' or val[1].split()[1]=='str') and (val[0] == "monomer_file_name"\
                or val[0] == "topology" or val[0] == "trajectory") :
                    exec "test = self.%s" % (val[0])
                    if (test == "NA") :
                        exec "self.%s = []" % (val[0])
                        exec 'self.%s += [np.array(%s).astype(%s)]' % (val[0],w[1:len(w)],val[1].split()[1])

                    else:
                        exec 'self.%s += [np.array(%s).astype(%s)]' % (val[0],w[1:len(w)],val[1].split()[1])


                #if type is an array of int, float, or str
                elif val[1].split()[0]=='array' and (val[1].split()[1]=='int' or val[1].split()[1]=='float' or val[1].split()[1]=='str'):
                    exec 'self.%s=np.array(%s).astype(%s)'%(val[0],w[1:len(w)],val[1].split()[1])

                else:
                    print "unrecognised type for keyword %s: %s"%(w[0],val[1])
                    sys.exit(1)

            line = f.readline()

        f.close()


    #verify whether values are alright and alerting user, giving the correct values to the self.paramters to be transfered to Data
    def check_standard_variables(self):

        #if needed, init repellers
        if self.repel == 'on' :
            self.repel=True
            #repel_factor should be < 1!
            #self.repel_factor=0.05
        elif self.repel == 'off':
            self.repel=False
            self.repel_factor=0
        if self.repel != False and self.repel != True:
            print 'ERROR: repulsion should either be "on" or "off"!'
            sys.exit(1)

        #check restart frequency
        if self.restart_freq>self.max_steps:
            print "ERROR: restart frequency should be smaller than total number of steps!"
            sys.exit(1)
        if self.restart_freq==0:
            self.restart_freq=int(float(self.max_steps)/10.0)
            #print ">>> a restart file will be created every %s steps"%self.restart_freq

        #check restart file existence
        if self.restart_load!="NA" and os.path.isfile(self.restart_load)!=1:
            print "ERROR: restart file %s not found"%self.restart_load
            sys.exit(1)

        #check inertia values
        if self.inertia_max>1:
            print 'ERROR: maximal inertia should be smaller than 1!'
            sys.exit(1)
        if self.inertia_min<0:
            print 'ERROR: minimal inertia should be greater than 0!'
            sys.exit(1)
        if self.inertia_max<self.inertia_min :
            print 'ERROR: maximal inertia is lower than minimal inertia (or one of these values are undefined)!'
            sys.exit(1)

        #check neighborhood conditions
        if self.neigh_type!="geographic" and self.neigh_type!="indexed":
            print "ERROR: neighborType should be either geographic either indexed"
            sys.exit(1)

        #check kick and reseed threshold value
        if self.kar<0:
            print "ERROR: kick and reseed (kar) threshold should be greater than 0!"
            sys.exit(1)

        #check boundaries consistency
        if len(self.high_input)!=len(self.low_input):
            print "ERROR: boundaryMin and boundaryMax should have the same length!"
            sys.exit(1)

        if len(self.high_input)!=len(self.boundary_type) and self.boundary_type[0]!="NA":
            print "ERROR: boundaryType length inconsistent with low and high boundary length!"
            print 'ERROR: %s dimensions given, but %s needed!'%(len(self.boundary_type),len(self.low_input))
            sys.exit(1)

        if self.high_input!="NA" and (self.low_input>self.high_input).any():
            print 'ERROR: a lower boundary condition is greated than a higher one'
            print self.low_input
            print self.high_input
            sys.exit(1)

        if self.dimensions>-1 and self.high_input!="NA":
            print "ERROR: either dimensions or boundaryMin and boundaryMax variables should be used to defind space size!"
            sys.exit(1)


class Space(AbstractSpace):
    low=[]
    high=[]
    boundary_type=[]
    cell_size=[]

    def check_boundaries(self,p,v):
    ####PERIODIC###
    #high periodic boundary
        test=np.logical_and(p>self.high,self.boundary_type==0)
        while test.any() :
            p[test]-=self.cell_size[test]
            test=np.logical_and(p>self.high,self.boundary_type==0)

        #low periodic boundary
        #p_tmp=deepcopy(p)
        test=np.logical_and(p<self.low,self.boundary_type==0)
#        number = 0
        while test.any() :

            p[test]+=self.cell_size[test]

            test=np.logical_and(p<self.low,self.boundary_type==0)

        ###REFLEXIVE###
        #high boundary
        p_tmp=deepcopy(p)
        test=np.logical_and(p>self.high,self.boundary_type==1)
        while test.any() :
            p_tmp[test]=2*self.high[test]-p[test]
            p[test]=deepcopy(p_tmp[test])
            test=np.logical_and(p>self.high,self.boundary_type==1)
        v[test]*=-1

        #low boundary
        test=np.logical_and(p<self.low,self.boundary_type==1)
        while test.any() :
            p_tmp[test]=2*self.low[test]-p[test]
            p[test]=deepcopy(p_tmp[test])
            test=np.logical_and(p<self.low,self.boundary_type==1)
        v[test]*=-1

        return p,v


class BaseFitness(AbstractFitness):
    '''
    A class that serves as a bridge between AbstractFitness in c++ and the
    true Fitness implementation by the module programmer.

    It inherits from AbstractFitness, and needs to be inherited in the Fitness
    class.
    '''
    
    def __init__(self):
        '''
        The constructor.

        NOTE TO THE MODULE PROGRAMMER:
        Please, make the call similar to this while implementing the derived
        function. This is needed because of the integration with c++. Sample
        code would be like this:

        class Fitness(BaseFitness):
            def __init__(self, other_params):
                BaseFitness.__init__(self)

                #your_code
        '''
        AbstractFitness.__init__(self)

    def evaluation(self, particle):
        '''
        method that is called from PSO in c++ for evaluating the particle

        NOTE TO THE MODULE PROGRAMMER:
        instead of using evaluate() method, it might be better to override
        and use this method and use the particle object instead. It should
        give much more freedom.

        @param particle - object of Particle class that contains all the
                        necessary information
        @return - value at the position of the particle, float
        '''

        # pseudocode:
        #positionList = arrayToList(particle.getPosition(), posSize)
        #return self.evaluate(particle.getIndex(), pos_list)

        raise NotImplementedError("TODO BY IVAN")  # TODO

    def evaluate(self, num, pos):
        '''
        method that should be implemented by the module programmer, which
        performs the actual evaluation of the particle

        @param num - the index of the particle, integer
        @param pos - the position of the particle,
                     list of coordinates, of length d
        '''
        raise NotImplementedError("call of not implemented evaluate()")


class Postprocess:


        #extract from log file just the solution with lowest fitness (below a defined threshold)
    def select_solutions(self,params):

            #loading logfile
        l=[]
        infile=open(params.output_file,"rb") # -> the log.txt file
        for line in infile :
            l.append(line.split())

        infile.close()

        #filter the log
        all_log=np.array(l).astype(float) # the 1.09909e+02 of log file
#           print "all_log"
#           print all_log


        filt=all_log[all_log[:,-1]<params.accept,2:len(all_log)] # first is selecting lines and second is column, boolean indexing, slicing
#           print "len(all_log)"
#           print len(all_log)
#           print "filt"
#           print filt

        #if no solution matching filtering criteria is found, return 10 best
        if len(filt)==0:
            print "WARNING: No solution below desired threshold ("+str(params.accept)+"), returning best 10 solution instead"
            pos=np.argsort(all_log[:,-1]) # sort the array for the lowest fitness values, this arrays is just an index order, make a[pos] to get the right one
            self.filter_log=all_log[pos[0:10],2:len(all_log)] # takes the top 10 lowest fitness values

        else:
            pos=np.argsort(filt[:,-1])
            self.filter_log=filt[pos,:]

        #write complexes selected by filtering
        f_log=open("filtered_log.dat","w")
        for line in self.filter_log: # iterate over all the elements of the log array
            for item in line: #
                f_log.write("%s "%item)
            f_log.write("\n")
        f_log.close()

        return self.filter_log


    #old filtering function... returns unranked solutions
    def select_solutions_unranked(self,params):

        #loading logfile
        l=[]
        infile=open(params.output_file,"rb")
        for line in infile :
            l.append(line.split()) # -> [[1.1.2],[,1,2,12]]

        infile.close()
        all_log=np.array(l).astype(float)
        self.filter_log=all_log[all_log[:,-1]<params.accept,2:len(all_log)]

        #write complexes selected by filtering
        f_log=open("filtered_log.dat","w")
        for line in self.filter_log:
            for item in line:
                f_log.write("%s "%item)
            f_log.write("\n")
        f_log.close()

        if len(self.filter_log)==0:
            print "WARNING: No solution below desired threshold, returning best 10 solution instead"
            pos=np.argsort(all_log[:,-1])
            self.filter_log=all_log[pos[0:10],2:len(all_log)] # modified to 20 from 10

        return self.filter_log


    def distance_clustering(self,params) : # done on the self.filter_log obtained from select_solutions() above

        clusters_file=open("dist_clusters.dat","w")

        print ">> clustering best solutions according to search space distance..."
        P=self.filter_log[:,0:len(self.filter_log[0,:])] #points list
        print "P"
        print P

        V=self.filter_log[:,-1] #values of best hits
        print "V"
        print V
        C=[] #centroids array
        P_C=np.zeros(len(P)) #points-to-cluster mapping
        C_V=[] #centroids values
        cnt=0 #centroids counter

        #cluster accepted solutions
        while(True) :
            #check if new clustering loop is needed
            k=np.nonzero(P_C==0)[0]
            if len(k)!=0 :
                cnt=cnt+1
                P_C[k[0]]=cnt
                a=P[k[0]]
                C.append(a)
            else :
                break

            #clustering loop
            new_addition=True
            print ">>> building cluster %s"%cnt
            while(new_addition) :
                new_addition=False

                for i in xrange(0,len(k),1) :
                    distance=np.sqrt(np.dot(C[cnt-1]-P[k[i]],C[cnt-1]-P[k[i]]))
                    if distance<params.cluster_threshold :
                        P_C[k[i]]=cnt
                        pos_sum=np.zeros(len(P[1]))
                        n=np.nonzero(P_C==cnt)[0]

                        for j in xrange(0,len(n),1):
                            pos_sum=pos_sum+P[n[j]]
                        C[cnt-1]=pos_sum/len(n)

                #set centroid score with score of closes neighbor in set
                q=np.nonzero(P_C==cnt)[0]
                distance=10000
                targ=0
                for i in xrange(0,len(q),1) :
                    d=np.sqrt(np.dot(C[cnt-1]-P[q[i]],C[cnt-1]-P[q[i]]))
                    if d<distance :
                        distance=d
                        targ=q[i]
                C_V.append(V[targ])

                #generate output log
                for item in C[cnt-1]:
                    clusters_file.write("%s "%item)
                clusters_file.write("%s\n"%C_V[cnt-1])
        clusters_file.close()
        return

    # Xx Calculate the RMSD between 2 monomers
    #Kabsch alignement algorithm
    #see: http://www.pymolwiki.org/index.php/Kabsch#The_Code
    def align(self,m1, m2):

        L = len(m1)

        ##protein is already centered, don't need centering!
        #COM1 = np.sum(m1,axis=0) / float(L)
        #COM2 = np.sum(m2,axis=0) / float(L)
        #m1 -= COM1
        #m2 -= COM2

        E0 = np.sum( np.sum(m1*m1,axis=0),axis=0) + np.sum( np.sum(m2*m2,axis=0),axis=0)

        #This beautiful step provides the answer. V and Wt are the orthonormal
        # bases that when multiplied by each other give us the rotation matrix, U.
        # S, (Sigma, from SVD) provides us with the error!  Isn't SVD great!
        V, S, Wt = np.linalg.svd( np.dot( np.transpose(m2), m1))

        reflect = float(str(float(np.linalg.det(V) * np.linalg.det(Wt))))

        if reflect == -1.0:
            S[-1] = -S[-1]
            V[:,-1] = -V[:,-1]

        RMSD = E0 - (2.0 * sum(S))
        RMSD = np.sqrt(abs(RMSD / L))

        return RMSD
