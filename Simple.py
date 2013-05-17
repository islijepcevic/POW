from Default import Parser as P
from Default import Space as S
from Default import Postprocess as PP

import numpy as np


class Fitness:

    def __init__(self,data,params):
        pass

    def evaluate(self,num,pos):
        #print pos
        dimensions=len(pos)
        return np.sum(np.sin(np.radians(pos)))/dimensions+1.0

class Space(S):
    def __int__(self, params, data):
        pass
    

class Parser(P):
    def __init__(self):
        pass
    def check_variables(self):
        pass

class Data:
    def __init__(self,params):
        pass      

class Postprocess(PP):

    def __init__(self,data,params):
        pass

    def run(self) :
        pass    
