import numpy as np

def constraint_check(multimer):

    #neighborhood selection
    all2 = multimer.atomselect(2,"A","*","*")
    all3 = multimer.atomselect(3,"A","*","*")

    ##interfacing res 1
    glu55 = multimer.atomselect(1, "A", 55, "*")
    dist1_1=multimer.distance(glu55,all2)	
    dist1_2=multimer.distance(glu55,all3)	
    dist1=np.min([dist1_1,dist1_2])
    if dist1<4 and dist1>2:
        dist1=4

    #interfacing res 2
    lys115 = multimer.atomselect(1, "A", 115, "*")
    dist2_1=multimer.distance(lys115,all2)
    dist2_2=multimer.distance(lys115,all3)
    dist2=np.min([dist2_1,dist2_2])
    if dist2<4 and dist2>2:
        dist2=4

    #direct interaction
    phe64_1 = multimer.atomselect(1, "A", 64, "CE1")
    phe64_3 = multimer.atomselect(3, "A", 64, "CE1")
    dist3=multimer.distance(phe64_1,phe64_3)	
    if dist3<5:
        dist3=5


    return dist1, dist2, dist3

